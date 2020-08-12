#include "SeekBehaviour.h"
#include "GameObject.h"
#include <iostream>
SeekBehaviour::SeekBehaviour() :Behaviour() 
{
	m_target;
	m_targetRadi;
}

SeekBehaviour::~SeekBehaviour()
{
}

void SeekBehaviour::Update(GameObject* obj, float deltaTime)
{

	float toTargetDir = Vector2Distance(obj->GetPosition(), m_target);//Movement of the agent to the direction of the desired location. 
	if (toTargetDir < m_targetRadi)//If the Direction to the target is less than the radius of the target, then it will start to slow down.
	{
		if (m_onArriveFunc)//starts the lambda function of arriving at destination.
			m_onArriveFunc();
	}
	float headingLen = 400;
	Vector2 dirHeading = Vector2Add(obj->GetPosition(), obj->GetVelocity());//The direction the agent is heading in relation to the desired location.
	Vector2 dirToTarget = Vector2Normalize(Vector2Subtract(m_target, obj->GetPosition()));//Finding a singular unit between the targets location and the current location.
	Vector2 vecToTarget = Vector2Scale(dirToTarget, headingLen);//The vector distance from the agent to the location, multiplying the normalized singular point and the direction length
	Vector2 tarForcePos = Vector2Add(vecToTarget, obj->GetPosition());//How much force in terms of a vector should be applied to move from current position to the target location.
	Vector2 forceDir = Vector2Subtract(tarForcePos, dirHeading);//The force direction is the subtraction of the force - the direction of the heading.
	obj->ApplyForce(forceDir);//This is then applied to the force.

}

void SeekBehaviour::Draw(GameObject* obj)
{
	DrawCircle(m_target.x, m_target.y, m_targetRadi, GREEN);//Creates a larger outter circle from the target spot
	DrawCircle(m_target.x, m_target.y, 5, BLUE);//Creates a small outta circle from the target spot
}

const Vector2& SeekBehaviour::GetTarget() const
{
	return m_target;//Gets the location
	// TODO: insert return statement here
}

void SeekBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;//Sets the location in relation to the variable m_target.
}

const float SeekBehaviour::GetTargetRadius() const
{
	return m_targetRadi;
	// TODO: insert return statement here
}

void SeekBehaviour::SetTargetRadius(const float targetRad)
{
	m_targetRadi = targetRad;
}

void SeekBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArriveFunc = callback;
}
