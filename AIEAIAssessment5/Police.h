#pragma once

#include "GameObject.h"

class SeekBehaviour;
class WanderBehaviour;
class Player;

class Police : public GameObject
{
public:
	Police();
	~Police();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	SeekBehaviour* m_seekBehaviour;
	WanderBehaviour* m_wanderBehaviour;

	Player* m_playerDetails;
	Police* m_police;

private:

};

