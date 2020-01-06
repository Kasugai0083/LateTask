#include <math.h>
#include "Lib.h"
#include "Camera.h"

static D3DXVECTOR3 g_CameraPos = D3DXVECTOR3(0.0f,75.0f, -200.0f);
static D3DXVECTOR3 g_EyePos = D3DXVECTOR3(0.0f, 75.0f, 0.0f);
static const D3DXVECTOR3 *g_TargetPos = NULL;
static float g_CameraDeg = 0.0f;

void CameraPosUpdate();

const D3DXVECTOR3 *GetCameraPos()
{
	return &g_CameraPos;
}

const D3DXVECTOR3 *GetEyePos()
{
	return &g_EyePos;
}

void SetCameraPos(D3DXVECTOR3 pos)
{
	g_CameraPos = pos;
}

void SetEyePos(D3DXVECTOR3 pos)
{
	g_EyePos = pos;
}

void SetTarget(const D3DXVECTOR3 *target)
{
	g_TargetPos = target;
}

void CameraInit(const D3DXVECTOR3 *target)
{
	g_TargetPos = target;
	CameraPosUpdate();
}

void CameraUpdate()
{
	float speed = 2.0f;
	bool is_change = false;

	if (GetKey(KEY_CODE_LEFT))
	{
		g_CameraDeg += speed;
		is_change = true;
	}
	else if (GetKey(KEY_CODE_RIGHT)) 
	{
		g_CameraDeg -= speed;
		is_change = true;
	}

	if (is_change == false)
	{
		return;
	}

	CameraPosUpdate();
}

void CameraPosUpdate()
{
	if (g_TargetPos == NULL)
	{
		return;
	}

	float rad = g_CameraDeg * 3.14f / 180.0f;
	float distance = 400.0f;
	D3DXVECTOR3 vec = D3DXVECTOR3(
		sinf(rad) * distance,
		0.0f,
		-cosf(rad) * distance
	);

	g_CameraPos.x = g_TargetPos->x + vec.x;
	g_CameraPos.z = g_TargetPos->z + vec.z;
}