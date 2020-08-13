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

	for (int i = 0; i < moneyStorage.size(); i++)
	{
		DrawCircle(moneyStorage.at(i)->GetPosition().x, moneyStorage.at(i)->GetPosition().y, radius, YELLOW);
	}
}
void MoneyBags::Update(float deltaTime)
{
	float randValuex = rand() % 1080;//Gets a random location in the space of the maps
	float randValuey = rand() % 720;
	m_app->GetPlayer();
	m_time += deltaTime;
	if (moneyStorage.empty() == true || m_time > m_newTime)
	{
		MoneyBags* newMoney = new MoneyBags(m_app);
		newMoney->SetPosition({ randValuex, randValuey });
		moneyStorage.push_back(newMoney);
		m_time = 0;
	}
	for (int i = 0; i < moneyStorage.size(); i++)
	{
		if (m_player->GetPosition().x + m_player->GetInnerRadius() + radius > moneyStorage.at(i)->GetPosition().x
			&& m_player->GetPosition().x < moneyStorage.at(i)->GetPosition().x + m_player->GetInnerRadius() + radius
			&& m_player->GetPosition().y + m_player->GetInnerRadius() + radius > moneyStorage.at(i)->GetPosition().y
			&& m_player->GetPosition().y < moneyStorage.at(i)->GetPosition().y + m_player->GetInnerRadius() + radius)
		{//Find a way to delete a position in a vector.
			//moneyStorage.at(i);
			moneyStorage.pop_back();
		}
		
	}

}


