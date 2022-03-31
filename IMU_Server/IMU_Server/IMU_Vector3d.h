#pragma once
#pragma pack(8)
#ifdef IMU_ServerExport
#define IMU_Server_API __declspec(dllexport)
#else 
#define IMU_Server_API __declsepc(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	IMU_Server_API struct IMU_Vector3d {
		float x, y, z;
	};
#ifdef __cplusplus
}
#endif

