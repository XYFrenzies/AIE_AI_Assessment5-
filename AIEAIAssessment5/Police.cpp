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

	m_pFBehaviour->SetTargetRadius(20);
	m_wanderBehaviour->SetRadius(100);
	m_wanderBehaviour->SetDistance(10);

	m_pFBehaviour->OnArrive([this]() {//When the player left clicks and the agent arrives to the destination
		SetBehaviour(m_wanderBehaviour);//It returns to the wanderBehaviour
		});


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
	m_app->GetPlayer();


	//If the player is within the range of the police.
	if (m_player->GetPosition().x + m_player->GetOuttaRadius() + GetOuttaRadius() > GetPosition().x
		&& m_player->GetPosition().x < GetPosition().x + m_player->GetOuttaRadius() + GetOuttaRadius()
		&& m_player->GetPosition().y + m_player->GetOuttaRadius() + GetOuttaRadius() > GetPosition().y
		&& m_player->GetPosition().y < GetPosition().y + m_player->GetOuttaRadius() + GetOuttaRadius()
		&& m_behaviour == m_wanderBehaviour)
	{

		//This is for the nearby nodes around the police
		std::vector<Graph2D::Node*> closeNodesPol;
		m_app->GetGraph()->GetNearbyNodes(GetPosition(), radiusNode, closeNodesPol);

		//This is for the nearby nodes around the robbers
		std::vector<Graph2D::Node*> closeNodesRob;
		m_app->GetGraph()->GetNearbyNodes(m_app->GetPlayer()->GetPosition(), radiusNode, closeNodesRob);

		//If there is a path to the player.
		if (!closeNodesPol.empty() && !closeNodesRob.empty())
		{
			auto isGoalNode = [&](Graph2D::Node* node) {
				return node == closeNodesRob[0];
			};//Made a lambda function for the use of the pathfinding algorithm
			std::list<Graph2D::Node*> path;
			m_app->GetGraph()->PathFinder(closeNodesPol[0], isGoalNode, path);

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

void Police::Draw()
{

	float rot = atan2f(m_facingDir.y, m_facingDir.x) * (180.0f / 3.141592653589793238463f);

	float tw = (float)m_policeTexture.width;
	float th = (float)m_policeTexture.height;

	DrawTexturePro(m_policeTexture,
		{ 0.0f, 0.0f, (float)m_policeTexture.width, (float)m_policeTexture.height },
		{ m_pos.x, m_pos.y, tw, th },
		{ tw * 0.5f, th * 0.5f },
		rot, WHITE);

	DrawCircle(m_pos.x, m_pos.y, 3, WHITE);


	GameObject::Draw();

}
