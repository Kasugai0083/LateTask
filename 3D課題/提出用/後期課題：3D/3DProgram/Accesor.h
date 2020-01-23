#pragma once

#include "DirectX.h"

class Accesor : public Singleton<Accesor>
{
public:
	DXStatus GetDXStatus() { return m_AcDXStatus; }

	void Update();

protected:
	DXStatus m_AcDXStatus;
private:
	friend Singleton<Accesor>;

	Accesor() {};
	virtual ~Accesor() {};

	Accesor(const Accesor&) = delete;
	Accesor& operator=(const Accesor&) = delete;
	Accesor(const Accesor&&) = delete;
	Accesor& operator=(const Accesor&&) = delete;
};