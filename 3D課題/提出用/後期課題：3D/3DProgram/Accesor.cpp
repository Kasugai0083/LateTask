#include "Accesor.h"

DXManager* s_DXManager = DXManager::GetInstance();

void Accesor::Update() {
	s_DXManager->SendStatus(&m_AcDXStatus);
}