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
	for (auto money : moneyStorage)
	{
		DrawCircle(randValuex, randValuey, radius, YELLOW);
	}

}

void MoneyBags::Update(float deltaTime)
{
}
