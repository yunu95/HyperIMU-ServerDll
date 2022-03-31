#pragma once
#include <functional>
#include <list>
#include <thread>
#include <set>
#include <vector>
#include <iostream>
#include <winsock2.h> 
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <cstdio>
#include "IMU_data.h"
#include <mutex>

#ifdef IMU_ServerExport
#define IMU_Server_API __declspec(dllexport)
#else 
#define IMU_Server_API __declsepc(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
    class IMU_Server
    {
    private:
        static int portNum;
        static IMU_Server* instance;
        WSADATA wsaData; // 윈속 데이터 구조체.(WSAStartup() 사용할꺼!)
        SOCKADDR_IN ServerInfo; // 서버 주소정보 구조체
        SOCKADDR_IN FromClient; // 클라이언트에서 받는 주소정보 구조체

        std::list<std::function<void(const IMU_data&)>> IMU_DataCallbacks;
        std::vector<IMU_data> IMU_datasReceived;
        std::thread* socketLoopThread=NULL;
        //SOCKET serverSocket;
        int serverSocket;
        bool socketLoopPersistentFlag = true;

        IMU_Vector3d accel;
        IMU_Vector3d magnetometer;
        IMU_Vector3d gravity;
        IMU_Vector3d orientationEuler;
        IMU_Vector3d angularSpeed;
        std::mutex dataLock;

        std::tuple<std::string, float* > keywordTuple[15] = {
            {"accelerometer.x",&accel.x},{"accelerometer.y",&accel.y},{"accelerometer.z",&accel.z},
            {"magnetometer.x",&magnetometer.x},{"magnetometer.y",&magnetometer.y},{"magnetometer.z",&magnetometer.z},
            {"gyroscope.x",&angularSpeed.x},{"gyroscope.y",&angularSpeed.y},{"gyroscope.z",&angularSpeed.z},
            {"gravity.x",&gravity.x},{"gravity.y",&gravity.y},{"gravity.z",&gravity.z},
            {"orientation_sensor.x",&orientationEuler.x},{"orientation_sensor.y",&orientationEuler.y},{"orientation_sensor.z",&orientationEuler.z},
        };
        float* indexVectorMap[15] = {
            &accel.x,&accel.y,&accel.z,
            &magnetometer.x,&magnetometer.y,&magnetometer.z,
            &angularSpeed.x,&angularSpeed.y,&angularSpeed.z,
            &gravity.x,&gravity.y,&gravity.z,
            &orientationEuler.x,&orientationEuler.y,&orientationEuler.z,
        };

        IMU_Server();
        void socketLoop();
    public:
        ~IMU_Server();
        static IMU_Server* getInstance();
        static void setServerPortNumber(int portNumber);
        IMU_Vector3d getLatestAccel();
        IMU_Vector3d getLatestMagnetometer();
        IMU_Vector3d getLatestGravity();
        IMU_Vector3d getLatestOrientationEuler();
        IMU_Vector3d getLatestAngularSpeed();
        // activate coonection thread.
        void establishConnection();
        // activate coonection thread.
        void terminateConnection();
        // add callbacks which get called during data flush.
        void addIMU_DataCallback(std::function<void(const IMU_data& argument)>);
        // calls every data callback with arrived packet datas.
        void flushArrivedDatas();
    };
    IMU_Server_API void cleanUpObjects();
    IMU_Server_API void setServerPortNumber(int portNumber);
    IMU_Server_API void getLatestAccel(IMU_Vector3d*);
    IMU_Server_API void getLatestMagnetometer(IMU_Vector3d*);
    IMU_Server_API void getLatestGravity(IMU_Vector3d*);
    IMU_Server_API void getLatestOrientationEuler(IMU_Vector3d*);
    IMU_Server_API void getLatestAngularSpeed(IMU_Vector3d*);
#ifdef __cplusplus
}
#endif
