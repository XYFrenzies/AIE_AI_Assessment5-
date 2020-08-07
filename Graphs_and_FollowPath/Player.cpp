#include "Player.h"
#include "KeyBoardBehaviour.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WanderBehaviour.h"

Player::Player() : GameObject()
{
	m_kbBehaviour = new KeyBoardBehaviour();//Creates an instance in memory of the Keyboard behaviour 
	m_seekBehaviour = new SeekBehaviour();//Creates an instance in memory of the seek behaviour 
	m_fleeBehaviour = new FleeBehaviour();
	m_wanderBehaviour = new WanderBehaviour();
	m_seekBehaviour->SetTargetRadius(25);//Sets the radius of the circle
	m_fleeBehaviour->SetTargetRadius(25);//Sets the radius of the circle
	m_wanderBehaviour->SetRadius(25);//Sets the radius of the circle
	m_wanderBehaviour->SetDistance(10);//Sets distance of agent from the circle.
	m_seekBehaviour->OnArrive([this]() {//When the player left clicks and the agent arrives to the destination
		SetBehaviour(m_kbBehaviour);//It returns to the keyboard behaviour
	});
	m_fleeBehaviour->OutOfRange([this]() {
			SetBehaviour(m_kbBehaviour);
	});
	m_wanderBehaviour->ChangeMode([this]() {
		SetBehaviour(m_kbBehaviour);
		});

	SetBehaviour(m_kbBehaviour);//Automatically sets the behaviour to the keyboard behaviour
}

Player::~Player()
{
	SetBehaviour(nullptr);
	delete m_kbBehaviour;
	delete m_seekBehaviour;
	delete m_fleeBehaviour;
	delete m_wanderBehaviour;
}

void Player::Update(float deltaTime)
{
	if (IsMouseButtonDown(0))
	{
		m_seekBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_seekBehaviour);
	}
	else if (IsMouseButtonDown(1))
	{
		m_fleeBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_fleeBehaviour);
	}
	else if (IsKeyPressed(KEY_Q))
	{
		SetBehaviour(m_wanderBehaviour);//Allws for the agent to move around
	}
	else if (IsKeyPressed(KEY_R))
	{
		SetBehaviour(m_kbBehaviour);//Returns back to the keyboard behaviour when the player presses "r"
	}
	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}
