#pragma once
#include "Behaviour.h"
#include "time.h"
#include <stdlib.h>
#include "raymath.h"
#include <functional>


class WanderBehaviour : public Behaviour
{
public:
	WanderBehaviour();
	virtual ~WanderBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);

	void Draw(GameObject* obj);

	Vector2 AngleToSet(Vector2 vector, float newValue);

	void ChangeMode(std::function<void()> callback);
	//==================================================================
	//Sets the radius of the circle.
	void SetRadius(const float radius);
	const float GetRadius() const;
	//==================================================================
	//This is for setting the distance between the circle and the agent
	void SetDistance(const float dis);
	const float GetDistance() const;
	//==================================================================

protected:

	std::function<void()> m_ChangeMode;

private:
	float m_angle = 0;

	float m_circDis = 80.0f;
	float m_circRad = 50.0f;
	float m_angleToWander = 0.0f;
	const float m_changeInAngle = 5;
	float m_time = 0.0f;
	int m_changeinDegrees = 20;

	//DEBUG
	Vector2 debug_circleCenter;
	Vector2 debug_displacement;


};

