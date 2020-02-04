#include "HandMade.h"


namespace HandMade {

	void Translation(D3DXMATRIX* matrix_, float x_, float y_, float z_) {
		D3DXMatrixIdentity(matrix_);

		matrix_->_41 += x_;
		matrix_->_42 += y_;
		matrix_->_43 += z_;

	}
	void BillBoard(D3DXMATRIX* out_, D3DXMATRIX* in_) {
		D3DXMatrixIdentity(out_);

		D3DXMatrixInverse(out_, NULL, in_);

		out_->_41 = 0.f;
		out_->_42 = 0.f;
		out_->_43 = 0.f;

	}

	void Scaling(D3DXMATRIX* matrix_, float x_, float y_, float z_) {
		D3DXMatrixIdentity(matrix_);

		matrix_->_11 = x_;
		matrix_->_22 = y_;
		matrix_->_33 = z_;

	}

	void RotationX(D3DXMATRIX* matrix_, float radian_) {
		D3DXMatrixIdentity(matrix_);

		matrix_->_22 = cosf(radian_);
		matrix_->_23 = sinf(radian_);
		matrix_->_32 = -sinf(radian_);
		matrix_->_33 = cosf(radian_);

	}

	void RotationY(D3DXMATRIX* matrix_, float radian_) {
		D3DXMatrixIdentity(matrix_);

		matrix_->_11 = cosf(radian_);
		matrix_->_13 = -sinf(radian_);
		matrix_->_31 = sinf(radian_);
		matrix_->_33 = cosf(radian_);

	}
	void RotationZ(D3DXMATRIX* matrix_, float radian_) {
		D3DXMatrixIdentity(matrix_);

		matrix_->_11 = cosf(radian_);
		matrix_->_12 = sinf(radian_);
		matrix_->_21 = -sinf(radian_);
		matrix_->_22 = cosf(radian_);

	}

	void InverseMatrix(D3DXMATRIX* out_, D3DXMATRIX* in_)
	{
		D3DXMatrixInverse(out_, NULL, in_);
	}
}