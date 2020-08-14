#include "MoneyBags.h"
#include "Player.h"
#include "Application.h"


MoneyBags::MoneyBags(Application* app) : GameObject()
{
	srand(time(nullptr));
	m_app = app;

	m_moneyBagTex = LoadTexture("./assets/Sprites/MoneyBag.png");//Creates a texture of the moneybag

}

MoneyBags::~MoneyBags()
{
	UnloadTexture(m_moneyBagTex);//Unloads the sprite of the moneybag
	delete m_app;//Deletes the pointer of the application.
	m_app = nullptr;
}

void MoneyBags::Draw()
{
	//Draws the money
	for (int i = 0; i < moneyStorage.size(); i++)
		DrawCircle(moneyStorage.at(i)->GetPosition().x, moneyStorage.at(i)->GetPosition().y, radius, YELLOW);
}
void MoneyBags::Update(float deltaTime)
{
	float randValuex = rand() % 1080;//Gets a random location in the space of the maps on the x coord
	float randValuey = rand() % 720;//Gets a random location in the space of the maps on the y coord
	m_app->GetPlayer();//Gets the player information
	m_time += deltaTime;//Increases time by delta time
	if (moneyStorage.empty() == true || m_time > 5)//If there is nothing in the storage and/or the time is greater than a default time.
	{
		MoneyBags* newMoney = new MoneyBags(m_app);//Create a new money variable
		newMoney->SetPosition({ randValuex, randValuey });//Set the location of it
		moneyStorage.push_back(newMoney);//push it to a vector
		m_time = 0;//Set the time to 0
	}
	for (int i = 0; i < moneyStorage.size(); i++)//loops through the vector of money.
	{
		//If the player is colliding with the money
		if (m_player->GetPosition().x + m_player->GetInnerRadius() + radius > moneyStorage.at(i)->GetPosition().x
			&& m_player->GetPosition().x < moneyStorage.at(i)->GetPosition().x + m_player->GetInnerRadius() + radius
			&& m_player->GetPosition().y + m_player->GetInnerRadius() + radius > moneyStorage.at(i)->GetPosition().y
			&& m_player->GetPosition().y < moneyStorage.at(i)->GetPosition().y + m_player->GetInnerRadius() + radius)
		{
			moneyStorage.erase(moneyStorage.begin() + i);//Delete the money variable 
			moneyTaken = true;//The money has been taken.
		}
		
	}

}


