#pragma once

#include "GameObject.h"
#include <vector>
class SeekBehaviour;
class WanderBehaviour;
class PathFindingBehaviour;
class Player;
class Graph2DEditor;
class Graph2D;
class Application;

class Police : public GameObject
{
public:
	Police(Application *app);
	~Police();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void SetPlayer(Player* player) 
	{
		m_player = player;
	}

protected:
	SeekBehaviour* m_seekBehaviour;
	WanderBehaviour* m_wanderBehaviour;
	Application* m_app = nullptr;
	PathFindingBehaviour* m_pFBehaviour;
	Texture2D m_policeTexture;
	Player* m_player;

	float radiusNode = 75.0f;



private:

};

