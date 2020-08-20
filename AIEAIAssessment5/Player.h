#pragma once

#include "GameObject.h"

class Police;
class KeyBoardBehaviour;
class FleeBehaviour;
class WanderBehaviour;
class PathFindingBehaviour;
class Graph2DEditor;
class Application;
class Item;

class Player : public GameObject
{
public:
	Player(Application *app);//Constructor
	~Player();//Deconstructor

	virtual void Update(float deltaTime);
	virtual void Draw();
	//Sets the editor.
	void SetEditor(Graph2DEditor* editor);
	//Sets the item money.
	void SetMoney(Item* items) 
	{
		m_item = items;
	}

	bool isCaught = false; //Checks if the player is caught
protected:
	KeyBoardBehaviour* m_kbBehaviour;//Keyboard behaviuour
	FleeBehaviour* m_fleeBehaviour;//flee behaviuour
	WanderBehaviour* m_wanderBehaviour;//wander behaviuour

	PathFindingBehaviour* m_pFBehaviour;//pathfinding behaviuour

	Application* m_app = nullptr;//application
	Graph2DEditor* m_graph2DEditor = nullptr;//graph2Deditor for the setting of the editor

	Texture2D m_playerTexture;//Creates the player texture
	Item* m_item;//creates the instance of an item in memory

	bool m_fleedPrev = false;//Checks if the player is fleeing
	bool m_isKBBehaviour = false;//Checks if the player is in keyboard.



private:
};

