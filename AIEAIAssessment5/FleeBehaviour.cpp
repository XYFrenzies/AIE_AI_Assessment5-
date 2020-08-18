#include "FleeBehaviour.h"
#include "GameObject.h"

FleeBehaviour::FleeBehaviour() : Behaviour()
{
	m_fleeTarget;
	m_radiusOfTar;
}

FleeBehaviour::~FleeBehaviour()
{
}

void FleeBehaviour::Update(GameObject* obj, float deltaTime)
{
	Vector2 vecOfDestPos = Vector2Subtract(obj->GetPosition(), m_fleeTarget);//Gets the vector distance of the objects position to the fleeing target location
	float distance = Vector2Distance({ obj->GetPosition().x + obj->GetOuttaRadius(), obj->GetPosition().y + obj->GetOuttaRadius() }, 
		{ m_fleeTarget.x +  obj->GetOuttaRadius(),m_fleeTarget.y + obj->GetOuttaRadius() });//The integer distance is of the position and the fleeing target
	if (distance > m_radiusOfTar)//If the distance is larger than the radius, the velocity will decrease and the lamder function will occur
	{
		//-obj->GetVelocity().x, -obj->GetVelocity().y;//Lessens the velocity over time.
		if (m_outOfRangeFunc)
			m_outOfRangeFunc;
	}
	else
	{
		Vector2 dirHeading = Vector2Add(obj->GetPosition(), obj->GetVelocity());//Getting the direction that it will face, the addition of the objects position and its velocity
		float headingLen = Vector2Length(dirHeading);//Length in which it is heading.
		Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(vecOfDestPos), headingLen);//The velocity it needs to move
		Vector2 steeringForce = Vector2Subtract(desiredVelocity, obj->GetVelocity());//The movement that it makes to go.
		obj->ApplyForce(steeringForce);
	}
}

void FleeBehaviour::Draw(GameObject* obj)
{
	if (IsKeyPressed(KEY_TAB))
	{
		DrawCircle(m_fleeTarget.x, m_fleeTarget.y, m_radiusOfTar, GRAY);//Creates a larger outter circle from the target spot
		DrawCircle(m_fleeTarget.x, m_fleeTarget.y, 5, PINK);//Creates a small outta circle from the target spot
	}

}

const Vector2& FleeBehaviour::GetTarget() const
{
	return m_fleeTarget;
	// TODO: insert return statement here
}

void FleeBehaviour::SetTarget(const Vector2& target)
{
	m_fleeTarget = target;
}

const float& FleeBehaviour::GetTargetRadius() const
{
	return m_radiusOfTar;
}

void FleeBehaviour::SetTargetRadius(const float& targetRad)
{
	m_radiusOfTar = targetRad;
}

void FleeBehaviour::OutOfRange(std::function<void()> callback)
{
	m_outOfRangeFunc = callback;
}
