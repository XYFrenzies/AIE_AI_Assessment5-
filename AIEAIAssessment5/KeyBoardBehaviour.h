#pragma once
#include "Behaviour.h"
#include <iostream>
class KeyBoardBehaviour : public Behaviour
{
public:
	KeyBoardBehaviour();
	KeyBoardBehaviour(int up, int down, int left, int right, float move);
	virtual ~KeyBoardBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
protected:
	int m_upKey;
	int m_downKey;
	int m_leftKey;
	int m_rightKey;
	float m_moveForce = 0.0f;

private:

};

