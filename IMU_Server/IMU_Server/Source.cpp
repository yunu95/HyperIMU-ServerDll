////////////////////////////////////����//////////////////////////////////////////////
#include <stdio.h>
#include <iostream>
#include <winsock2.h> // ���� ��� ���� 
#include <windows.h> 
#include <WS2tcpip.h>
#include "IMU_Server.h"

#pragma comment (lib,"ws2_32.lib") // ���� ���̺귯�� ��ũ
#define BUFFER_SIZE 1024 // ���� ������

using namespace std;

void main(void)
{
    IMU_Server::setServerPortNumber(5471);
    int a = 0;
    cout << "asdasd";
    while (true) {
        a++;
        cout << IMU_Server::getInstance()->getLatestAccel().x << ",";
        cout << IMU_Server::getInstance()->getLatestAccel().y << ",";
        cout << IMU_Server::getInstance()->getLatestAccel().z << "\n";

        if (a % 200 == 0) {
            delete IMU_Server::getInstance();
            IMU_Server::setServerPortNumber(5471);
        }
        if (a % 200 == 100) {
            delete IMU_Server::getInstance();
            IMU_Server::setServerPortNumber(5353);
        }
    }
    //int a;
    //cin>>a;
    //WSADATA wsaData; // ���� ������ ����ü.(WSAStartup() ����Ҳ�!)
    //SOCKET serverSocket; // ���� ����
    //SOCKADDR_IN ServerInfo; // ���� �ּ����� ����ü
    //SOCKADDR_IN FromClient; // Ŭ���̾�Ʈ���� �޴� �ּ����� ����ü

    //int FromClient_Size; // Ŭ���̾�Ʈ�κ��� �޴� �޽��� ũ��
    //int Recv_Size; // �޴� ������
    //int Send_Size; // ������ ������
    //int Count;
    //char Buffer[BUFFER_SIZE];
    //short ServerPort = 5555; // ���� ��Ʈ��ȣ

    ////WSAStartup�� WS2_32.DLL�� �ʱ�ȭ �ϴ� �Լ�
    //if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) // WSAStartup �������� ���� �߻��ϸ�
    //{
    //    cout << "WinSock �ʱ�ȭ�κп��� ���� �߻� " << endl;
    //    WSACleanup(); // WS2_32.DLL�� ��� ����
    //}

    //// memset : ����ڰ� ���� �޸� ũ�⸸ŭ �޸� ������ Ư���� ������ ä��
    //memset(&ServerInfo, 0, sizeof(ServerInfo)); // 0���� �ʱ�ȭ
    //memset(&FromClient, 0, sizeof(FromClient));
    //memset(Buffer, 0, BUFFER_SIZE);

    //ServerInfo.sin_family = AF_INET; // IPv4 �ּ�ü�� ��� 
    ////ServerInfo.sin_addr.s_addr = inet_addr("127.0.0.1"); // ������ IP. �� ȥ�ڳ��̿�..
    //InetPton(AF_INET, (PCWSTR)("127.0.0.1"), &ServerInfo.sin_addr.s_addr);
    //ServerInfo.sin_port = htons(ServerPort); // ��Ʈ��ȣ

    //// ���� ����
    //serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // udp�� ���� ����. SOCK_DGRAM : UDP ���
    //if (serverSocket == INVALID_SOCKET) // ���� �߻���
    //{
    //    cout << "������ �����Ҽ� �����ϴ�." << endl;
    //    closesocket(serverSocket);
    //    WSACleanup();
    //    exit(0);
    //}

    ////// bind() - ���� ���� Ŭ���̾�Ʈ�� ���� welcome ����
    ////// ���޸� �Ҳ��� �ʿ����
    ////if (bind(serverSocket, (struct sockaddr*)&ServerInfo, //���ε� ���Ͽ� �������� �ο�
    ////    sizeof(ServerInfo)) == SOCKET_ERROR)
    ////{
    ////    cout << "���ε带 �� �� �����ϴ�." << endl;
    ////    closesocket(serverSocket);
    ////    WSACleanup();
    ////    exit(0);
    ////}

    //while (1)
    //{
    //    FromClient_Size = sizeof(FromClient);
    //    // recvfrom : UDP��� �񿬰���.  ��Ŷ����
    //    Recv_Size = recvfrom(serverSocket, Buffer, BUFFER_SIZE, 0,
    //        (struct sockaddr*)&FromClient, &FromClient_Size);
    //    Buffer[Recv_Size] = 0;
    //    char FromAddrStr[INET_ADDRSTRLEN];

    //    if (Recv_Size < 0)
    //    {
    //        cout << "recvfrom() error!" << endl;
    //        exit(0);
    //    }

    //    cout << "��Ŷ���ŵ�! ��Ŷ�� ���� Ŭ���̾�Ʈ�� " << inet_ntop(FromClient.sin_family,&FromClient.sin_addr,FromAddrStr,INET_ADDRSTRLEN) << endl;
    //    cout << "��Ŷ�� �����ʹ� " << Buffer << endl;

    //    //  ��Ŷ�۽�
    //    Send_Size = sendto(serverSocket, Buffer, Recv_Size, 0,
    //        (struct sockaddr*)&FromClient, sizeof(FromClient));
    //    if (Send_Size != Recv_Size)
    //    {
    //        cout << "sendto() error!" << endl;
    //        exit(0);
    //    }
    //}
    //closesocket(serverSocket); // ������ �ݽ��ϴ�.
    //WSACleanup();
}