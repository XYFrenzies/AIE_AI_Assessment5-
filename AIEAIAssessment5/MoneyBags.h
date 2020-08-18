#pragma once
#include <stdlib.h>
#include <vector>
#include "GameObject.h"
class Player;
class Application;

struct Money
{
	int value;
	Vector2 coord;
	float radius = 35;
};
class Item : public GameObject
{
public:
	//Constructor
	Item(Application* app);
	//Deconstructor
	~Item();
	
	virtual void Draw();
	virtual void Update(float deltaTime);
	//Sets the player in the application to the known player.
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	Money* HoldItemPos(float x, float y);//This is to hold all the available spots for the money to spawn

	bool moneyTaken = false;//public variable to find the money taken
	bool newMoney = false;
	std::vector<Money*> moneyStorage;//Storage of moneybags
	std::vector<Money*> drawnStorage;
protected:
private:
	Player* m_player;//the instance of a player
	Application* m_app = nullptr;//The application is set to nullptr

	Texture2D m_coinTex;
	float m_time;
	const float m_newTime = 10;
	float radius = 8.0f;


};

