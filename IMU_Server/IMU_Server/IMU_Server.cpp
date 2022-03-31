#include "IMU_Server.h"
////////////////////////////////////����//////////////////////////////////////////////

#pragma comment (lib,"ws2_32.lib") // ���� ���̺귯�� ��ũ
#define BUFFER_SIZE 1024 // ��Ŷ ���� ũ��

IMU_Server* IMU_Server::instance;
int IMU_Server::portNum;
IMU_Server::IMU_Server() {
    establishConnection();
}
IMU_Server::~IMU_Server() {
    if (socketLoopThread)
        terminateConnection();
    instance = NULL;
}
IMU_Server* IMU_Server::getInstance() {
    if (!instance)
        instance = new IMU_Server();
    return instance;
}
void IMU_Server::setServerPortNumber(int portNumber) {
    IMU_Server::portNum = portNumber;
}
IMU_Vector3d IMU_Server::getLatestAccel() {
    //dataLock.lock();
    auto value = accel;
    //dataLock.unlock();
    return value;
}
IMU_Vector3d IMU_Server::getLatestMagnetometer() {
    //dataLock.lock();
    auto value = magnetometer;
    //dataLock.unlock();
    return value;
}
IMU_Vector3d IMU_Server::getLatestGravity() {
    //dataLock.lock();
    auto value = gravity;
    //dataLock.unlock();
    return value;
}
IMU_Vector3d IMU_Server::getLatestOrientationEuler() {
    //dataLock.lock();
    auto value = orientationEuler;
    //dataLock.unlock();
    return value;
}
IMU_Vector3d IMU_Server::getLatestAngularSpeed() {
    //dataLock.lock();
    auto value = angularSpeed;
    //dataLock.unlock();
    return value;
}
void IMU_Server::IMU_Server::socketLoop() {

    int FromClient_Size; // Ŭ���̾�Ʈ�κ��� �޴� �޽��� ũ��
    int Recv_Size; // �޴� ������
    char Buffer[BUFFER_SIZE];
    short ServerPort = portNum; // ���� ��Ʈ��ȣ

    //WSAStartup�� WS2_32.DLL�� �ʱ�ȭ �ϴ� �Լ�
    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) // WSAStartup �������� ���� �߻��ϸ�
    {
        std::cout << "WinSock �ʱ�ȭ�κп��� ���� �߻� " << std::endl;
        WSACleanup(); // WS2_32.DLL�� ��� ����
    }

    // memset : ����ڰ� ���� �޸� ũ�⸸ŭ �޸� ������ Ư���� ������ ä��
    memset(&ServerInfo, 0, sizeof(ServerInfo)); // 0���� �ʱ�ȭ
    memset(&FromClient, 0, sizeof(FromClient));
    memset(Buffer, 0, BUFFER_SIZE);

    ServerInfo.sin_family = AF_INET; // IPv4 �ּ�ü�� ��� 
    //ServerInfo.sin_addr.s_addr = inet_addr("127.0.0.1"); // ������ IP. �� ȥ�ڳ��̿�..
    //InetPton(AF_INET, (PCWSTR)("127.0.0.1"), &ServerInfo.sin_addr.s_addr);
    ServerInfo.sin_port = htons(ServerPort); // ��Ʈ��ȣ

    // ���� ����
    serverSocket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0);
    //serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // udp�� ���� ����. SOCK_DGRAM : UDP ���
    if (serverSocket == INVALID_SOCKET) // ���� �߻���
    {
        std::cout << "������ �����Ҽ� �����ϴ�." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // bind() - ���� ���� Ŭ���̾�Ʈ�� ���� welcome ����
    // ���޸� �Ҳ��� �ʿ����
    if (bind(serverSocket, (struct sockaddr*)&ServerInfo, //���ε� ���Ͽ� �������� �ο�
        sizeof(ServerInfo)) == SOCKET_ERROR)
    {
        std::cout << "���ε带 �� �� �����ϴ�." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }
    timeval tv;
    fd_set fds;
    int reuseAddress = 1;
    tv.tv_sec = 0;
    tv.tv_usec = 500;

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuseAddress, sizeof(reuseAddress)))
        return;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&tv), sizeof(timeval)))
        return;
    while (socketLoopPersistentFlag)
    {
        FromClient_Size = sizeof(FromClient);
        FD_ZERO(&fds);
        FD_SET(serverSocket, &fds);
        // recvfrom : UDP��� �񿬰���.  ��Ŷ����
        Recv_Size = select(serverSocket, &fds, NULL, NULL, &tv);
        //Recv_Size = recvfrom(serverSocket, Buffer, BUFFER_SIZE, 0, (struct sockaddr*)&FromClient, &FromClient_Size);
        //Buffer[Recv_Size] = 0;
        if (Recv_Size == 0)
            continue;
        if (Recv_Size == -1) {
            //auto a = WSAGetLastError();
            perror("select");
            return;
        }
        std::string bufferStr(Buffer);
        Recv_Size = recvfrom(serverSocket, Buffer, BUFFER_SIZE, 0, (struct sockaddr*)&FromClient, &FromClient_Size);

        std::stringstream stringSplitStream(bufferStr);
        std::string floatString;
        int splitStringIndex = 0;
        dataLock.lock();
        while (std::getline(stringSplitStream, floatString, ',')) {
            if (splitStringIndex >= 15)
                break;
            *indexVectorMap[splitStringIndex] = std::stof(floatString);
            splitStringIndex++;
        }
        dataLock.unlock();
    }

}

// activate coonection thread.
void IMU_Server::establishConnection() {
    if (socketLoopThread)
        terminateConnection();
    socketLoopPersistentFlag = true;
    socketLoopThread = new std::thread([this] {this->socketLoop(); });
}
void IMU_Server::terminateConnection() {
    socketLoopPersistentFlag = false;
    socketLoopThread->join();
    delete socketLoopThread;
    closesocket(serverSocket); // ������ �ݽ��ϴ�.
    WSACleanup();
    socketLoopThread = NULL;
}
// add callbacks which get called during data flush.
void IMU_Server::addIMU_DataCallback(std::function<void(const IMU_data& argument)> callback) {
    IMU_DataCallbacks.push_back(callback);
}
IMU_Server_API void cleanUpObjects() {
    delete IMU_Server::getInstance();
}
void setServerPortNumber(int portNumber) {
    //delete IMU_Server::getInstance();
    IMU_Server::setServerPortNumber(portNumber);
    //IMU_Server::getInstance();
}
void getLatestAccel(IMU_Vector3d* data) {
    *data = IMU_Server::getInstance()->getLatestAccel();
}
void getLatestMagnetometer(IMU_Vector3d* data) {
    *data = IMU_Server::getInstance()->getLatestMagnetometer();
}
void getLatestGravity(IMU_Vector3d* data) {
    *data = IMU_Server::getInstance()->getLatestGravity();
}
void getLatestOrientationEuler(IMU_Vector3d* data) {
    *data = IMU_Server::getInstance()->getLatestOrientationEuler();
}
void getLatestAngularSpeed(IMU_Vector3d* data) {
    *data = IMU_Server::getInstance()->getLatestAngularSpeed();
}
