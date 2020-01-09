#pragma once

#include <d3d9.h>
#include <d3dx9.h>

void HandMadeTranslation(D3DXMATRIX* matrix_, float x_, float y_, float z_);

void HandMadeBillBoard(D3DXMATRIX* out_, D3DXMATRIX* in_);

void HandMadeScaling(D3DXMATRIX* matrix_, float x_, float y_, float z_);

void HandMadeRotationX(D3DXMATRIX* matrix_, float radian_);
void HandMadeRotationY(D3DXMATRIX* matrix_, float radian_);
void HandMadeRotationZ(D3DXMATRIX* matrix_, float radian_);

void HandMadeMultiply(D3DXMATRIX* matrix_, D3DXMATRIX* matrix2_, D3DXMATRIX* matrix3_);

void InverseViewMatrix(D3DXMATRIX* out_, D3DXMATRIX* in_);
