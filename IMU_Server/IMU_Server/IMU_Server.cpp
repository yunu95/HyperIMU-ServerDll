#include "IMU_Server.h"
////////////////////////////////////서버//////////////////////////////////////////////

#pragma comment (lib,"ws2_32.lib") // 윈속 라이브러리 링크
#define BUFFER_SIZE 1024 // 패킷 버퍼 크기

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

    int FromClient_Size; // 클라이언트로부터 받는 메시지 크기
    int Recv_Size; // 받는 사이즈
    char Buffer[BUFFER_SIZE];
    short ServerPort = portNum; // 서버 포트번호

    //WSAStartup은 WS2_32.DLL을 초기화 하는 함수
    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) // WSAStartup 설정에서 문제 발생하면
    {
        std::cout << "WinSock 초기화부분에서 문제 발생 " << std::endl;
        WSACleanup(); // WS2_32.DLL의 사용 끝냄
    }

    // memset : 사용자가 정한 메모리 크기만큼 메모리 영역을 특정한 값으로 채움
    memset(&ServerInfo, 0, sizeof(ServerInfo)); // 0으로 초기화
    memset(&FromClient, 0, sizeof(FromClient));
    memset(Buffer, 0, BUFFER_SIZE);

    ServerInfo.sin_family = AF_INET; // IPv4 주소체계 사용 
    //ServerInfo.sin_addr.s_addr = inet_addr("127.0.0.1"); // 루프백 IP. 즉 혼자놀이용..
    //InetPton(AF_INET, (PCWSTR)("127.0.0.1"), &ServerInfo.sin_addr.s_addr);
    ServerInfo.sin_port = htons(ServerPort); // 포트번호

    // 소켓 생성
    serverSocket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0);
    //serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // udp용 소켓 생성. SOCK_DGRAM : UDP 사용
    if (serverSocket == INVALID_SOCKET) // 에러 발생시
    {
        std::cout << "소켓을 생성할수 없습니다." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // bind() - 새로 오는 클라이언트를 받을 welcome 소켓
    // 전달만 할꺼면 필요없음
    if (bind(serverSocket, (struct sockaddr*)&ServerInfo, //바인드 소켓에 서버정보 부여
        sizeof(ServerInfo)) == SOCKET_ERROR)
    {
        std::cout << "바인드를 할 수 없습니다." << std::endl;
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
        // recvfrom : UDP통신 비연결형.  패킷수신
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
    closesocket(serverSocket); // 소켓을 닫습니다.
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
