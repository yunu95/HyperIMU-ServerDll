#pragma once

#ifdef IMU_ServerExport
#define IMU_Server_API __declspec(dllexport)
#else 
#define IMU_Server_API __declsepc(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	IMU_Server_API struct IMU_Quaternion {
		float x, y, z, w;
	};
#ifdef __cplusplus
}
#endif
