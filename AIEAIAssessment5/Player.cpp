#include "Player.h"
#include "KeyBoardBehaviour.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WanderBehaviour.h"
#include "PathFindingBehaviour.h"
#include "Police.h"
#include "Graph2DEditor.h"
#include "Application.h"
#include "MoneyBags.h"

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
	m_pFBehaviour->SetTargetRadius(m_innerRadius);
	m_seekBehaviour->OnArrive([this]() {//When the player left clicks and the agent arrives to the destination
		SetVelocity({ 0, 0 });
		SetBehaviour(m_kbBehaviour);//It returns to the keyboard behaviour
		});
	m_fleeBehaviour->OutOfRange([this]() {
		SetBehaviour(m_wanderBehaviour);
		});
	m_wanderBehaviour->ChangeMode([this]() {
		SetBehaviour(m_kbBehaviour);
		});
	m_pFBehaviour->OnArrive([this]() {//When the player left clicks and the agent arrives to the destination
		SetBehaviour(m_wanderBehaviour);//It returns to the keyboard behaviour
		});

	SetBehaviour(m_wanderBehaviour);//Automatically sets the behaviour to the keyboard behaviour

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

	//Incase something happens with the player, it can be converted back to the keyboard behaviour.
	if (IsKeyPressed(KEY_R))
	{
		SetBehaviour(m_kbBehaviour);//Returns back to the keyboard behaviour when the player presses "r"
		m_isKBBehaviour = true;
	}
	if(IsKeyDown(KEY_Q) && m_behaviour == m_kbBehaviour)
	{
		SetBehaviour(m_wanderBehaviour);//Returns back to the keyboard behaviour when the player presses "r"
		m_isKBBehaviour = false;
	}
	//If the moneybag has spawned on the map.
	if (((m_behaviour == m_wanderBehaviour && !m_app->GetMoney()->moneyStorage.empty()) 
		|| (m_behaviour == m_pFBehaviour && m_fleedPrev == true) || 
		(!m_app->GetMoney()->moneyStorage.empty() && m_behaviour != m_pFBehaviour)) && m_isKBBehaviour == false)
	{
		m_fleedPrev = false;
		//This is for the nearby nodes around the player
		std::vector<Graph2D::Node*> closeNodesRob;
		m_app->GetGraph()->GetNearbyNodes(GetPosition(), GetInnerRadius(), closeNodesRob);

		//This is for the nearby nodes around the moneyBag
		std::vector<Graph2D::Node*> closeNodesMon;
		m_app->GetGraph()->GetNearbyNodes(m_app->GetMoney()->moneyStorage.back()->GetPosition(), m_app->GetMoney()->moneyStorage.back()->GetInnerRadius(), closeNodesMon);

		//If there is a path to the player.
		if (!closeNodesRob.empty() && !closeNodesMon.empty())
		{
			auto isGoalNode = [&](Graph2D::Node* node) {
				return node == closeNodesMon[0];
			};//Made a lambda function for the use of the pathfinding algorithm
			std::list<Graph2D::Node*> path;
			m_app->GetGraph()->PathFinder(closeNodesRob[0], isGoalNode, path);

			std::vector<Vector2> newPath;
			for (auto graphPath : path)
			{
				newPath.push_back(graphPath->data);
			}
			m_pFBehaviour->AddPath(newPath);

			m_pFBehaviour->OnArrive([this]() {
				SetBehaviour(m_wanderBehaviour);
				});

			SetBehaviour(m_pFBehaviour);
		}
	}


	GameObject::Update(deltaTime);
}

void Player::Draw()
{

	float rot = atan2f(m_facingDir.y, m_facingDir.x) * (150.0f / 3.141592653589793238463f);

	float tw = (float)m_playerTexture.width;
	float th = (float)m_playerTexture.height;

	DrawTexturePro(m_playerTexture,
		{ 0.0f, 0.0f, (float)m_playerTexture.width, (float)m_playerTexture.height },
		{ m_pos.x, m_pos.y, tw, th },
		{ tw * 0.5f, th * 0.5f },
		rot, WHITE);

	GameObject::Draw();
}

void Player::SetEditor(Graph2DEditor* editor)
{
	m_graph2DEditor = editor;
}
