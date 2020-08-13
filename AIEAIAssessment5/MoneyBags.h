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
	MoneyBags(Application* app);
	~MoneyBags();

	virtual void Draw();
	virtual void Update(float deltaTime);
	//const Vector2& GetPosition() const
	//{

	//	return {randValuex, randValuey};
	//	// TODO: insert return statement here
	//}
	void SetPlayer(Player* player)
	{
		m_player = player;
	}

	bool moneyTaken = false;
protected:
private:

	Player* m_player;
	Application* m_app = nullptr;
	std::vector<MoneyBags*> moneyStorage;

	float m_time;
	const float m_newTime = 10;
	float radius = 8.0f;

};

