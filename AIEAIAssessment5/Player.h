#pragma once

#include "GameObject.h"

class Police;
class KeyBoardBehaviour;
class SeekBehaviour;
class FleeBehaviour;
class WanderBehaviour;
class PathFindingBehaviour;
class Graph2DEditor;
class Application;

class Player : public GameObject
{
public:
	Player(Application *app);
	~Player();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void SetEditor(Graph2DEditor* editor);



protected:

	KeyBoardBehaviour* m_kbBehaviour;
	SeekBehaviour* m_seekBehaviour;
	FleeBehaviour* m_fleeBehaviour;
	WanderBehaviour* m_wanderBehaviour;

	PathFindingBehaviour* m_pFBehaviour;

	Application* m_app = nullptr;
	Graph2DEditor* m_graph2DEditor = nullptr;

	Texture2D m_playerTexture;

private:
};

