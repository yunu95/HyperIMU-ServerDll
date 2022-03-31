////////////////////////////////////서버//////////////////////////////////////////////
#include <stdio.h>
#include <iostream>
#include <winsock2.h> // 윈속 헤더 포함 
#include <windows.h> 
#include <WS2tcpip.h>
#include "IMU_Server.h"

#pragma comment (lib,"ws2_32.lib") // 윈속 라이브러리 링크
#define BUFFER_SIZE 1024 // 버퍼 사이즈

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
    //WSADATA wsaData; // 윈속 데이터 구조체.(WSAStartup() 사용할꺼!)
    //SOCKET serverSocket; // 소켓 선언
    //SOCKADDR_IN ServerInfo; // 서버 주소정보 구조체
    //SOCKADDR_IN FromClient; // 클라이언트에서 받는 주소정보 구조체

    //int FromClient_Size; // 클라이언트로부터 받는 메시지 크기
    //int Recv_Size; // 받는 사이즈
    //int Send_Size; // 보내는 사이즈
    //int Count;
    //char Buffer[BUFFER_SIZE];
    //short ServerPort = 5555; // 서버 포트번호

    ////WSAStartup은 WS2_32.DLL을 초기화 하는 함수
    //if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) // WSAStartup 설정에서 문제 발생하면
    //{
    //    cout << "WinSock 초기화부분에서 문제 발생 " << endl;
    //    WSACleanup(); // WS2_32.DLL의 사용 끝냄
    //}

    //// memset : 사용자가 정한 메모리 크기만큼 메모리 영역을 특정한 값으로 채움
    //memset(&ServerInfo, 0, sizeof(ServerInfo)); // 0으로 초기화
    //memset(&FromClient, 0, sizeof(FromClient));
    //memset(Buffer, 0, BUFFER_SIZE);

    //ServerInfo.sin_family = AF_INET; // IPv4 주소체계 사용 
    ////ServerInfo.sin_addr.s_addr = inet_addr("127.0.0.1"); // 루프백 IP. 즉 혼자놀이용..
    //InetPton(AF_INET, (PCWSTR)("127.0.0.1"), &ServerInfo.sin_addr.s_addr);
    //ServerInfo.sin_port = htons(ServerPort); // 포트번호

    //// 소켓 생성
    //serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // udp용 소켓 생성. SOCK_DGRAM : UDP 사용
    //if (serverSocket == INVALID_SOCKET) // 에러 발생시
    //{
    //    cout << "소켓을 생성할수 없습니다." << endl;
    //    closesocket(serverSocket);
    //    WSACleanup();
    //    exit(0);
    //}

    ////// bind() - 새로 오는 클라이언트를 받을 welcome 소켓
    ////// 전달만 할꺼면 필요없음
    ////if (bind(serverSocket, (struct sockaddr*)&ServerInfo, //바인드 소켓에 서버정보 부여
    ////    sizeof(ServerInfo)) == SOCKET_ERROR)
    ////{
    ////    cout << "바인드를 할 수 없습니다." << endl;
    ////    closesocket(serverSocket);
    ////    WSACleanup();
    ////    exit(0);
    ////}

    //while (1)
    //{
    //    FromClient_Size = sizeof(FromClient);
    //    // recvfrom : UDP통신 비연결형.  패킷수신
    //    Recv_Size = recvfrom(serverSocket, Buffer, BUFFER_SIZE, 0,
    //        (struct sockaddr*)&FromClient, &FromClient_Size);
    //    Buffer[Recv_Size] = 0;
    //    char FromAddrStr[INET_ADDRSTRLEN];

    //    if (Recv_Size < 0)
    //    {
    //        cout << "recvfrom() error!" << endl;
    //        exit(0);
    //    }

    //    cout << "패킷수신됨! 패킷을 보낸 클라이언트는 " << inet_ntop(FromClient.sin_family,&FromClient.sin_addr,FromAddrStr,INET_ADDRSTRLEN) << endl;
    //    cout << "패킷의 데이터는 " << Buffer << endl;

    //    //  패킷송신
    //    Send_Size = sendto(serverSocket, Buffer, Recv_Size, 0,
    //        (struct sockaddr*)&FromClient, sizeof(FromClient));
    //    if (Send_Size != Recv_Size)
    //    {
    //        cout << "sendto() error!" << endl;
    //        exit(0);
    //    }
    //}
    //closesocket(serverSocket); // 소켓을 닫습니다.
    //WSACleanup();
}