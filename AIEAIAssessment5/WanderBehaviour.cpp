#include "WanderBehaviour.h"
#include "GameObject.h"
#include <iostream>

WanderBehaviour::WanderBehaviour() : Behaviour()
{
	srand(time(nullptr));
}

WanderBehaviour::~WanderBehaviour()
{
}

void WanderBehaviour::Update(GameObject* obj, float deltaTime)
{

	obj->SetFriction(0);
	m_time += deltaTime;
	Vector2 vel = obj->GetVelocity();
	if (m_time > 0.1)
	{
		if (obj->GetPosition().x > GetScreenWidth() - 20 ||
			obj->GetPosition().x < 20 ||
			obj->GetPosition().y < 20 ||
			obj->GetPosition().y > GetScreenHeight() - 20)//Checking if it interacts with the outta part of the screen
		{
			Vector2 newVel;
			newVel.x = GetScreenWidth() * 0.5f - obj->GetPosition().x;//Sets the direction that the player is facing, towards the center via the x
			newVel.y = GetScreenHeight() * 0.5f - obj->GetPosition().y;//Sets the direction that the player is facing, towards the center via the y

			newVel = Vector2Normalize(newVel);//
			newVel = Vector2Scale(newVel, obj->GetMaxSpeed());
			obj->SetVelocity(newVel);
		}
		else
		{
			Vector2 constVel = { 100.0f, 100.0f };
			if (obj->GetVelocity().x == 0.0f && obj->GetVelocity().y == 0.0f)
				obj->SetVelocity(constVel);

			float degreesTheta = atan2(obj->GetVelocity().x, obj->GetVelocity().y);//returns the tangent of the x and y value of the arc.
			degreesTheta *= 57.3248;//This is 180 / Pi to find the theta value around the circle converting it from radians to degrees

			float radius = obj->GetMaxSpeed();//  Vector2Distance({ 0, 0 }, obj->GetVelocity());// Its the distance from the point 0,0 and the velocity of the object

			float radiansTheta = (degreesTheta - m_changeinDegrees) + rand() % (2 * m_changeinDegrees);
			radiansTheta *= 0.017444;
			Vector2 changedVel;
			changedVel.x = radius * sinf(radiansTheta);
			changedVel.y = radius * cosf(radiansTheta);
			obj->SetVelocity(changedVel);
		}

		m_time = 0;

	}
}

Vector2 WanderBehaviour::AngleToSet(Vector2 vector, float newValue)
{
	float veclen = Vector2Length(vector);
	return { cosf(newValue) * veclen, sinf(newValue * veclen) };
}

void WanderBehaviour::ChangeMode(std::function<void()> callback)
{
	m_ChangeMode = callback;
}

void WanderBehaviour::SetRadius(const float radius)
{
	m_circRad = radius;
}

const float WanderBehaviour::GetRadius() const
{
	return m_circRad;
}

void WanderBehaviour::SetDistance(const float dis)
{
	m_circDis = dis;
}

const float WanderBehaviour::GetDistance() const
{
	return m_circDis;
}
