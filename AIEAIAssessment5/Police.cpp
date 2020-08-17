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

	//m_pFBehaviour->OnArrive([this]() {//When the player left clicks and the agent arrives to the destination
	//	//SetBehaviour(m_wanderBehaviour);//It returns to the wanderBehaviour
	//	});


	SetBehaviour(m_wanderBehaviour);

	m_policeTexture = LoadTexture("./assets/Sprites/hitman1_stand.png");
}

Police::~Police()
{
	SetBehaviour(nullptr);
	delete m_seekBehaviour;
	delete m_wanderBehaviour;
	delete m_pFBehaviour;
	UnloadTexture(m_policeTexture);
}

void Police::Update(float deltaTime)
{
	if (m_player->GetPosition().x + m_player->GetOuttaRadius() + GetOuttaRadius() > GetPosition().x
		&& m_player->GetPosition().x < GetPosition().x + m_player->GetOuttaRadius() + GetOuttaRadius()
		&& m_player->GetPosition().y + m_player->GetOuttaRadius() + GetOuttaRadius() > GetPosition().y
		&& m_player->GetPosition().y < GetPosition().y + m_player->GetOuttaRadius() + GetOuttaRadius())
	{
		SetBehaviour(m_pFBehaviour);
		m_isSeen = true;
		if (m_pFBehaviour)
		{
			std::vector<Graph2D::Node*> m_closeNodesRob;
			m_app->GetGraph()->GetNearbyNodes(m_app->GetPlayer()->GetPosition(), radiusNode, m_closeNodesRob);
			std::vector<Graph2D::Node*> m_closeNodesPol;
			m_app->GetGraph()->GetNearbyNodes(GetPosition(), radiusNode, m_closeNodesPol);

			if (!m_closeNodesRob.empty() && !m_closeNodesPol.empty())
			{
				std::list<Graph2D::Node*> gNodePath;
				m_app->GetGraph()->PathFinder(m_closeNodesRob[0], m_closeNodesPol[0], gNodePath);

				std::vector<Vector2> newPath;
				for (auto graphPath : gNodePath)
				{
					newPath.push_back(graphPath->data);
				}
				m_pFBehaviour->AddPath(newPath);

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
	float dt = GetFrameTime();
	m_time += dt;

	float rot = atan2f(m_facingDir.y, m_facingDir.x) * (180.0f / 3.141592653589793238463f);

	float tw = (float)m_policeTexture.width;
	float th = (float)m_policeTexture.height;

	DrawTexturePro(m_policeTexture,
		{ 0.0f, 0.0f, (float)m_policeTexture.width, (float)m_policeTexture.height },
		{ m_pos.x, m_pos.y, tw, th },
		{ tw * 0.5f, th * 0.5f },
		rot, WHITE);

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
