#ifndef CAMERA_H_
#define CAMERA_H_

struct Vector {
	float m_X, m_Y, m_Z;
};

typedef class Vector2 {
public:
	Vector2(float x, float y, float z):
	X(x),
	Y(y),
	Z(z)
	{}
	float X, Y, Z;
}Vec2;

class Camera {
public:
	Camera(Vec2 vec, Vec2 gaze):
	m_CameraPos(vec),
	m_Gaze(gaze)
	{}
	void Update();
private:
	Vec2 m_CameraPos;
	Vec2 m_Gaze;
};

#endif