#ifndef CAMERA_H_
#define CAMERA_H_


const D3DXVECTOR3 *GetCameraPos();
void SetCameraPos(D3DXVECTOR3 pos);
const D3DXVECTOR3 *GetEyePos();
void SetEyePos(D3DXVECTOR3 pos);
void SetTarget(const D3DXVECTOR3 *target);
void CameraInit(const D3DXVECTOR3 *target);
void CameraUpdate();

#endif
