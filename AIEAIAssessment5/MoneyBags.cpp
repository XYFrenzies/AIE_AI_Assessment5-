#include "MoneyBags.h"
#include "Player.h"
#include "Application.h"


MoneyBags::MoneyBags(Application* app) : GameObject()
{
	srand(time(nullptr));
	m_app = app;

}

MoneyBags::~MoneyBags()
{
}

void MoneyBags::Draw()
{
	//Draws the money
	for (int i = 0; i < drawnStorage.size(); i++)
		DrawCircle(drawnStorage.at(i)->coord.x, drawnStorage.at(i)->coord.y, radius, YELLOW);
}
void MoneyBags::Update(float deltaTime)
{

	m_app->GetPlayer();//Gets the player information
	m_time += deltaTime;//Increases time by delta time
	if (!moneyStorage.empty())//If there is nothing in the storage and/or the time is greater than a default time.
	{
		for (int i = 0; i < moneyStorage.size(); i++)
		{//Find a better way to randomly display the money at a good rate.
			float randValuex = GetRandomValue(0, 100);//Gets a random location in the space of the maps on the x coord
			float randValuey = GetRandomValue(0, 100);//Gets a random location in the space of the maps on the y coord
			if (moneyStorage.at(i)->coord.x == randValuex && moneyStorage.at(i)->coord.y == randValuey)
			{
				drawnStorage.push_back(moneyStorage.at(i));
			}

		}
	}
	for (int i = 0; i < drawnStorage.size(); i++)//loops through the vector of money.
	{
		//If the player is colliding with the money
		if (m_player->GetPosition().x + m_player->GetInnerRadius() + radius > drawnStorage.at(i)->coord.x
			&& m_player->GetPosition().x < drawnStorage.at(i)->coord.x + m_player->GetInnerRadius() + radius
			&& m_player->GetPosition().y + m_player->GetInnerRadius() + radius > drawnStorage.at(i)->coord.y
			&& m_player->GetPosition().y < drawnStorage.at(i)->coord.y + m_player->GetInnerRadius() + radius)
		{
			drawnStorage.erase(drawnStorage.begin() + i);//Delete the money variable 
			moneyTaken = true;//The money has been taken.
			newMoney = true;
		}

	}

}

Money* MoneyBags::HoldMoneyBags(float x, float y)
{
	Money* money = new Money();
	money->value = 1;
	money->coord = { x , y };
	moneyStorage.push_back(money);
	return money;
}



