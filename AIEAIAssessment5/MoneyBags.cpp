#include "MoneyBags.h"
#include "Player.h"
#include "Application.h"


Item::Item(Application* app) : GameObject()
{
	m_app = app;//An instance of the application in item

	m_coinTex = LoadTexture("./assets/Sprites/Coin.png");//The coin texture

	m_player = m_app->GetPlayer();//Player is initalised
	m_time = 0;//Time is set to 0;

}

Item::~Item()
{
	UnloadTexture(m_coinTex);
}

void Item::Draw()
{
	//Draws the coin
	float tw = (float)m_coinTex.width / 10;//Tile width
	float th = (float)m_coinTex.height / 10;//Tileheight
	for (int i = 0; i < drawnStorage.size(); i++)
	{
		DrawTexturePro(m_coinTex,
			{ 0.0f, 0.0f, (float)m_coinTex.width, (float)m_coinTex.height },
			{ drawnStorage.at(i)->coord.x, drawnStorage.at(i)->coord.y, tw, th },
			{ tw * 0.5f, th * 0.5f },
			0, WHITE);//This is to draw the coin
		//When the player presses tab, it checks for the radius of the coin.
		if (IsKeyDown(KEY_TAB))
		{
			DrawCircle(drawnStorage.at(i)->coord.x, drawnStorage.at(i)->coord.y, (float)m_coinTex.width / 20, {255, 0, 0, 100});
		}
	}
}
void Item::Update(float deltaTime)
{
	int randI = GetRandomValue(0, 620);
	m_app->GetPlayer();//Gets the player information
	m_time += deltaTime;//Increases time by delta time
	if (!moneyStorage.empty() && m_time > 5)//If there is nothing in the storage and/or the time is greater than a default time.
	{
		drawnStorage.push_back(moneyStorage.at(randI));
		m_time = 0;
	}
	for (int i = 0; i < drawnStorage.size(); i++)//loops through the vector of coins.
	{
		//If the player is colliding with the money
		if (m_player->GetPosition().x + m_player->GetInnerRadius() + (float)m_coinTex.width / 20 > drawnStorage.at(i)->coord.x
			&& m_player->GetPosition().x < drawnStorage.at(i)->coord.x + m_player->GetInnerRadius() + (float)m_coinTex.width / 20
			&& m_player->GetPosition().y + m_player->GetInnerRadius() + (float)m_coinTex.height / 20 > drawnStorage.at(i)->coord.y
			&& m_player->GetPosition().y < drawnStorage.at(i)->coord.y + m_player->GetInnerRadius() + (float)m_coinTex.height / 20)
		{
			drawnStorage.erase(drawnStorage.begin() + i);//Delete the item variable 
			moneyTaken = true;//The item has been taken.
			newMoney = true;
		}
	}
}

Money* Item::HoldItemPos(float x, float y)
{
	//This is checking for every available location to spawn a item.
	Money* money = new Money();
	money->value = 1;
	money->coord = { x , y };
	moneyStorage.push_back(money);
	return money;
}



