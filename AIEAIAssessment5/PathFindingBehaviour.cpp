#include "PathFindingBehaviour.h"
#include "GameObject.h"
PathFindingBehaviour::PathFindingBehaviour() : Behaviour()
{
}

PathFindingBehaviour::~PathFindingBehaviour()
{
}

void PathFindingBehaviour::Update(GameObject* obj, float deltaTime)
{
	AddPath(m_pathFind.m_path);
	if (pathAdded == false)
		return;
	if (!m_pathFind.m_path.empty())
	{
		float toTargetDir = Vector2Distance(obj->GetPosition(), m_targetNodes.front());//Movement of the agent to the direction of the desired location. 
		if (toTargetDir < m_targetRadi)//If the Direction to the target is less than the radius of the target, then it will start to slow down.
		{
			m_targetNodes.erase(m_targetNodes.begin());
		}
		Vector2 dirHeading = Vector2Add(obj->GetPosition(), obj->GetVelocity());//The direction the agent is heading in relation to the desired location.
		Vector2 dirToTarget = Vector2Normalize(Vector2Subtract(m_targetNodes.front(), obj->GetPosition()));//Finding a singular unit between the targets location and the current location.
		Vector2 vecToTarget = Vector2Scale(dirToTarget, toTargetDir);//The vector distance from the agent to the location, multiplying the normalized singular point and the direction length
		Vector2 tarForcePos = Vector2Add(vecToTarget, obj->GetPosition());//How much force in terms of a vector should be applied to move from current position to the target location.
		Vector2 forceDir = Vector2Subtract(tarForcePos, dirHeading);//The force direction is the subtraction of the force - the direction of the heading.
		obj->ApplyForce(forceDir);//This is then applied to the force.
	}
	else
	{
		if (m_onArriveFunc)//starts the lambda function of arriving at destination.
			m_onArriveFunc();
	}
}

void PathFindingBehaviour::Draw(GameObject* obj)
{
}

const Vector2& PathFindingBehaviour::GetTarget() const
{
	return m_target;
}

void PathFindingBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float PathFindingBehaviour::GetTargetRadius() const
{
	return m_targetRadi;
}

void PathFindingBehaviour::SetTargetRadius(const float targetRad)
{
	m_targetRadi = targetRad;
}

void PathFindingBehaviour::AddPath(std::vector<Vector2>& path)
{
	m_targetNodes = path;
	pathAdded = true;
}