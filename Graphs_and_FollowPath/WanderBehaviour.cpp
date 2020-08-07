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
	Vector2 vel = obj->GetVelocity();
	if (Vector2Length(vel) == 0)
	{
		vel = { 0, -1 };
	}
	//Calculates the centre circle
	//Them_circledistance to the agent, in the same direction as the current velocity
	Vector2 centCirc = Vector2Scale(Vector2Normalize(vel), m_circDis);

	//Defaults the displacement at 0, -1
	Vector2 displacement = { 0, 1 };
	displacement = Vector2Scale(displacement, m_circRad);
	displacement = AngleToSet(displacement, m_angleToWander);
	m_angleToWander += (rand() % (int)m_changeInAngle) - m_changeInAngle * .5;
	Vector2 forceOfMove = Vector2Add(centCirc, displacement);
	obj->ApplyForce(forceOfMove);
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
