#include "Police.h"
#include "SeekBehaviour.h"
#include "WanderBehaviour.h"
#include "Player.h"
Police::Police() : GameObject()
{


	m_seekBehaviour = new SeekBehaviour();
	m_wanderBehaviour = new WanderBehaviour();

	m_wanderBehaviour->SetRadius(100);
	m_wanderBehaviour->SetDistance(10);

	m_seekBehaviour->OnArrive([this]() {//When the player left clicks and the agent arrives to the destination
		SetBehaviour(m_wanderBehaviour);//It returns to the keyboard behaviour
		});


	SetBehaviour(m_wanderBehaviour);
}

Police::~Police()
{
	SetBehaviour(nullptr);
	delete m_seekBehaviour;
	delete m_wanderBehaviour;
}

void Police::Update(float deltaTime)
{

	//This is to check if the player is within a location of the other, it will seek towards the player.
	//if (m_playerDetails->GetOuttaRadius() <= m_wanderBehaviour->GetRadius())
	//{
	//	m_seekBehaviour->SetTarget(m_playerDetails->GetPosition());
	//	SetBehaviour(m_seekBehaviour);
	//}
}

void Police::Draw()
{
	GameObject::Draw();
}
