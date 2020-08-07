#pragma once

#include "GameObject.h"

class KeyBoardBehaviour;
class SeekBehaviour;
class FleeBehaviour;
class WanderBehaviour;

class Player : public GameObject
{
public:
	Player();
	~Player();

	virtual void Update(float deltaTime);
	virtual void Draw();
protected:

	KeyBoardBehaviour* m_kbBehaviour;
	SeekBehaviour* m_seekBehaviour;
	FleeBehaviour* m_fleeBehaviour;
	WanderBehaviour* m_wanderBehaviour;

private:
};

