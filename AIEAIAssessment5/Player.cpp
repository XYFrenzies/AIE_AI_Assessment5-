#include "Player.h"
#include "KeyBoardBehaviour.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WanderBehaviour.h"
#include "PathFindingBehaviour.h"
#include "Police.h"
#include "Graph2DEditor.h"
#include "Application.h"

Player::Player(Application* app) : GameObject()
{
	m_app = app;

	m_kbBehaviour = new KeyBoardBehaviour();//Creates an instance in memory of the Keyboard behaviour 
	m_seekBehaviour = new SeekBehaviour();//Creates an instance in memory of the seek behaviour 
	m_fleeBehaviour = new FleeBehaviour();
	m_wanderBehaviour = new WanderBehaviour();
	m_pFBehaviour = new PathFindingBehaviour();
	m_seekBehaviour->SetTargetRadius(100);//Sets the radius of the circle
	m_fleeBehaviour->SetTargetRadius(100);//Sets the radius of the circle
	m_wanderBehaviour->SetRadius(100);//Sets the radius of the circle
	m_wanderBehaviour->SetDistance(10);//Sets distance of agent from the circle.
	m_pFBehaviour->SetTargetRadius(20);
	m_seekBehaviour->OnArrive([this]() {//When the player left clicks and the agent arrives to the destination
		SetVelocity({0, 0});
		SetBehaviour(m_kbBehaviour);//It returns to the keyboard behaviour
	});
	m_fleeBehaviour->OutOfRange([this]() {
			SetBehaviour(m_kbBehaviour);
	});
	m_wanderBehaviour->ChangeMode([this]() {
		SetBehaviour(m_kbBehaviour);
		});
	m_pFBehaviour->OnArrive([this]() {//When the player left clicks and the agent arrives to the destination
		SetBehaviour(m_kbBehaviour);//It returns to the keyboard behaviour
		});

	SetBehaviour(m_kbBehaviour);//Automatically sets the behaviour to the keyboard behaviour

	m_playerTexture = LoadTexture("./assets/Sprites/survivor1_stand.png");


}

Player::~Player()
{
	SetBehaviour(nullptr);
	delete m_kbBehaviour;
	delete m_seekBehaviour;
	delete m_fleeBehaviour;
	delete m_wanderBehaviour;
	UnloadTexture(m_playerTexture);
}

void Player::Update(float deltaTime)
{
	auto mousePos = m_app->GetMousePosWorld();

	if (IsMouseButtonDown(0))
	{
		m_seekBehaviour->SetTarget(mousePos);
		SetBehaviour(m_seekBehaviour);
	}
	else if (IsMouseButtonDown(1))
	{
		m_fleeBehaviour->SetTarget(mousePos);
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
	else if (m_graph2DEditor && !m_graph2DEditor->m_path.empty() && IsKeyPressed(KEY_P))
	{
		m_pFBehaviour->AddPath(m_graph2DEditor->m_path);
		SetBehaviour(m_pFBehaviour);//Returns back to the keyboard behaviour when the player presses "r"
	}
	GameObject::Update(deltaTime);
}

void Player::Draw()
{

	float rot = atan2f(m_facingDir.y, m_facingDir.x) * (300.0f / 3.141592653589793238463f);

	float tw = (float)m_playerTexture.width;
	float th = (float)m_playerTexture.height;

	DrawTexturePro(m_playerTexture,
		{ 0.0f, 0.0f, (float)m_playerTexture.width, (float)m_playerTexture.height },
		{ m_pos.x, m_pos.y, tw, th },
		{ tw * 0.5f, th * 0.5f },
		rot, WHITE);

	DrawCircle(m_pos.x, m_pos.y, 3, WHITE);
}

void Player::SetEditor(Graph2DEditor* editor)
{
	m_graph2DEditor = editor;
}
