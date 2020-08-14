#pragma once
#include "time.h"
#include <stdlib.h>
#include <vector>
#include "GameObject.h"
class Player;
class Application;


class MoneyBags : public GameObject
{
public:
	//Constructor
	MoneyBags(Application* app);
	//Deconstructor
	~MoneyBags();
	
	virtual void Draw();
	virtual void Update(float deltaTime);
	//Sets the player in the application to the known player.
	void SetPlayer(Player* player)
	{
		m_player = player;
	}

	bool moneyTaken = false;//public variable to find the money taken
	std::vector<MoneyBags*> moneyStorage;//Storage of moneybags
protected:
private:
	
	Player* m_player;//the instance of a player
	Application* m_app = nullptr;//The application is set to nullptr

	Texture2D m_moneyBagTex;
	float m_time;
	const float m_newTime = 10;
	float radius = 8.0f;

};

