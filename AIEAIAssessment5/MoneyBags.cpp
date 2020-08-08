#include "MoneyBags.h"

MoneyBags::MoneyBags()
{
	srand(time(nullptr));
}

MoneyBags::~MoneyBags()
{
}

void MoneyBags::Draw()
{
	DrawCircle(randValuex, randValuey, radius, YELLOW);

}

void MoneyBags::Update(float deltaTime)
{
	//if (m_player->GetPosition().x == randValuex && m_player->GetPosition().y == randValuey)
	//{
	//	moneyStorage.erase()
	//}

}
