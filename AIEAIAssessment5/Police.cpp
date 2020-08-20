#include "Police.h"
#include "SeekBehaviour.h"
#include "WanderBehaviour.h"
#include "Player.h"
#include "Graph2D.h"
#include "Application.h"
#include "PathFindingBehaviour.h"
Police::Police(Application* app) : GameObject()
{
	m_app = app;

	m_seekBehaviour = new SeekBehaviour();
	m_wanderBehaviour = new WanderBehaviour();
	m_pFBehaviour = new PathFindingBehaviour();

	m_pFBehaviour->SetTargetRadius(35);
	m_pFBehaviour->SetConstSpeed(100);
	m_wanderBehaviour->SetRadius(100);
	m_wanderBehaviour->SetDistance(10);
	SetBehaviour(m_wanderBehaviour);

	m_player = m_app->GetPlayer();
	m_policeTexture = LoadTexture("./assets/Sprites/hitman1_stand.png");
}

Police::~Police()
{
	//Deletes the behaviours that the police has.
	SetBehaviour(nullptr);
	delete m_seekBehaviour;
	delete m_wanderBehaviour;
	delete m_pFBehaviour;
	UnloadTexture(m_policeTexture);
}

void Police::Update(float deltaTime)
{
	//This is a check for if the player is within the radius of the police.
	if (m_player->GetPosition().x + m_player->GetOuttaRadius() + GetOuttaRadius() > GetPosition().x
		&& m_player->GetPosition().x < GetPosition().x + m_player->GetOuttaRadius() + GetOuttaRadius()
		&& m_player->GetPosition().y + m_player->GetOuttaRadius() + GetOuttaRadius() > GetPosition().y
		&& m_player->GetPosition().y < GetPosition().y + m_player->GetOuttaRadius() + GetOuttaRadius())
	{
		//Set behaviour to pathfind
		SetBehaviour(m_pFBehaviour);
		m_isSeen = true;
		if (m_pFBehaviour)//If its in the pathfinding state...
		{
			std::vector<Graph2D::Node*> m_closeNodesRob;//Create a vector of nodes near the robber
			m_app->GetGraph()->GetNearbyNodes(m_app->GetPlayer()->GetPosition(), radiusNode, m_closeNodesRob);
			std::vector<Graph2D::Node*> m_closeNodesPol;//Create a vector of nodes near the police
			m_app->GetGraph()->GetNearbyNodes(GetPosition(), radiusNode, m_closeNodesPol);

			if (!m_closeNodesRob.empty() && !m_closeNodesPol.empty())//If neither are empty
			{
				std::list<Graph2D::Node*> gNodePath;//It creates a list to get the path from the pathfinding algorithm.
				m_app->GetGraph()->PathFinder(m_closeNodesRob[0], m_closeNodesPol[0], gNodePath);

				std::vector<Vector2> newPath;//Creates a vector in which a path will be sent to
				for (auto graphPath : gNodePath)
				{
					newPath.push_back(graphPath->data);
				}
				m_pFBehaviour->AddPath(newPath);//Adds the path.

				//If the police arrives at the destination ie: either it is out of range or it has captured the player.
				m_pFBehaviour->OnArrive([this]() {
					SetBehaviour(m_wanderBehaviour);
					m_isSeen = false;
					});
			}
		}
	}
	GameObject::Update(deltaTime);
}

void Police::Draw()
{
	float dt = GetFrameTime();//This is just so i can draw the police lights
	m_time += dt;

	float rot = atan2f(m_facingDir.y, m_facingDir.x) * (180.0f / 3.141592653589793238463f);//Rotation of police

	float tw = (float)m_policeTexture.width;//Tilewidth
	float th = (float)m_policeTexture.height;//TileHeight

	DrawTexturePro(m_policeTexture,
		{ 0.0f, 0.0f, (float)m_policeTexture.width, (float)m_policeTexture.height },
		{ m_pos.x, m_pos.y, tw, th },
		{ tw * 0.5f, th * 0.5f },
		rot, WHITE);//The texture of the player

	//This is if the player is seen by the police
	//If seen, the police with produce red and blue lights.
	if (m_isSeen == true)
	{
		if (m_time <= 0.5)
			DrawCircle(m_pos.x, m_pos.y, m_outtaRadius, { 255, 0, 0, 100 });

		else if (m_time > 0.5 && m_time <= 1)
			DrawCircle(m_pos.x, m_pos.y, m_outtaRadius, { 0, 0, 255, 100 });
		else
			m_time = 0;
	}
	GameObject::Draw();
}
