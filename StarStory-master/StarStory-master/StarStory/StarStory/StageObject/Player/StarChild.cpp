#include "StarChild.h"
#include "StarObject.h"
#include "../ObjectManager/ObjectManager.h"
#include "../Map/MapObject.h"
#include "../../Collision/Collision.h"

//------------------------------------
//�@�R���X�g���N�^
StarChild::StarChild(
	float x,
	float y,
	std::string tex_name,
	SoundResourceID se_id,
	Skill skill,
	float rot
) :ObjectBase(x, y, rot){

	m_width     = 46.f;
	m_height    = 64.f;
	m_tex_name  = tex_name;
	m_parent    = nullptr;
	m_map_obj   = ObjectManager::GetInstance().GetGameObjects<MapObject>();
	m_obj_width = 0.f;
	is_hit      = false;
	m_skill     = skill;
	m_cur_obj   = nullptr;
	m_se_id     = se_id;
	m_one_flame = 0;
}

//------------------------------------
//�@�X�V����
void StarChild::Update() {

	HitToObject();
	IsHit();
}

//------------------------------------
//�@�`�揈��
void StarChild::Draw() {

	SetVertex();
	Lib::DrawDiamond2D(
		m_tex_name.c_str(),
		m_vtx
	);
}

//-------------------------------------
//���_�̐ݒ�
void StarChild::SetVertex(DWORD color) {
	
	float ox = 0.5f;
	float oy = 0.5f;
	m_vtx[0] = { {(0.5f - ox),oy,0.5f,1.f}, color,{0.31f,0.5f} };
	m_vtx[1] = { {ox,(0.5f + oy), 0.5f,1.f},color,{0.5f,0.78f} };
	m_vtx[2] = { {(0.5f + ox),oy, 0.5f, 1.f},color,{0.69f,0.5f} };
	m_vtx[3] = { {ox,(0.5f - oy), 0.5f,1.f},color,{0.5f,0.228f} };

	DiamondLocalTransform(m_vtx, m_width, m_height);
	RefParentVertex(m_vtx);

}

//-------------------------------------
//�e�̍��W�����g�ɔ��f����
void StarChild::RefParentVertex(Vertex vtx[4]) {
	
	if (m_parent == nullptr) {
		m_parent = ObjectManager::GetInstance().FindObject(STAR_OBJ);
	}

	//�e�̍��W���擾
	float pos_x = m_parent->GetX();
	float pos_y = m_parent->GetY();
	
	//�e�̉�]�p���擾
	float sin = sinf(D3DXToRadian(m_parent->GetRot()));
	float cos = cosf(D3DXToRadian(m_parent->GetRot()));
	float vtx_pos_x = 0.f;
	float vtx_pos_y = 0.f;
	
	for (int i = 0; i < 4; ++i) {
		//���[�J�����WXY��ۑ�
		vtx_pos_x = vtx[i].pos.x;
		vtx_pos_y = vtx[i].pos.y;
		//��]�����������V���W��ݒ�
		float new_x = (vtx_pos_x * cos) + (vtx_pos_y * -sin);
		float new_y = (vtx_pos_x * sin) + (vtx_pos_y * cos);
		//���΍��W��ݒ肷��
		vtx[i].pos.x = new_x + pos_x;
		vtx[i].pos.y = new_y + pos_y;
	}
}

//--------------------------------------
//�@�I�u�W�F�N�g�Ƃ̓����蔻�����������
void StarChild::HitToObject() {

	SetVertex();
	//���g�̒��_�x�N�g��
	Vec2 vec = { m_vtx[1].pos.x, m_vtx[1].pos.y };

	for (auto obj : m_map_obj) {
		float right = obj->GetVertex(1).pos.x;
		//���_���I�u�W�F�N�g�̕��̒��Ȃ�ۑ�
		if (vec.x >= obj->GetX() && vec.x <= right) {
				m_cur_obj = obj;
		}
	}
}

void StarChild::IsHit() {

	SetVertex();
	Vec2 vec = { m_vtx[1].pos.x, m_vtx[1].pos.y };

	if (m_cur_obj == nullptr) {
		return;
	}

	float right = m_cur_obj->GetVertex(1).pos.x;
	if (vec.x >= m_cur_obj->GetX() && vec.x <= right) {
		//�}�b�v�ƒ��_���������Ă��邩
		if (IsHitToUpper(vec, m_cur_obj)) {
			++m_one_flame;
			PlaySE();
			is_hit = true;
		}
		else {
			is_hit = false;
		}
	}
}

//-------------------------------
//�@�����蔻��p�ϐ��Q�b�^�[
const bool StarChild::GetHit()const
{
	return is_hit;
}

//-------------------------------
//�@�X�L�����Q�b�^�[
const Skill StarChild::GetSkill()const {
	return m_skill;
}

//-------------------------------
// ���������}�b�v�I�u�W�F�N�g��Ԃ�
ObjectBase* StarChild::GetMapObj()const {
	
	if (m_cur_obj != nullptr) {
		return m_cur_obj;
	}
}

//--------------------------------------
//�}�b�v�I�u�W�F�N�g�Ƃ̂߂荞�݋������擾
float StarChild::GetDistanceToCeiling() {

	if (m_cur_obj != nullptr) {
		float obj_y = m_cur_obj->GetVertex(0).pos.y;
		return obj_y - m_vtx[1].pos.y;
	}
}

//---------------------------------
// SE����
void StarChild::PlaySE() {

	if (m_one_flame == 1) {
		SoundManager::GetInstanse().SoundPlayer(m_se_id, SoundManager::PLAY);
		m_one_flame = 0;
	}

}