#pragma once
#include "Player.h"
#include "time.h"
#include <stdlib.h>
#include <vector>
class MoneyBags
{
public:
	MoneyBags();
	~MoneyBags();

	void Draw();
	void Update(float deltaTime);
	//const Vector2& GetPosition() const
	//{

	//	return {randValuex, randValuey};
	//	// TODO: insert return statement here
	//}

protected:
private:
	float radius = 8.0f;
	Player* m_player;

	std::vector<MoneyBags*> moneyStorage;

	int randValuex = rand() % 1080;//Gets a random location in the space of the maps
	int randValuey = rand() % 720;
};

