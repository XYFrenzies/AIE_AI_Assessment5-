#pragma once
#include "Behaviour.h"
#include <iostream>
#include <functional>
#include "raymath.h"
class FleeBehaviour : public Behaviour
{
public:
	FleeBehaviour();
	virtual ~FleeBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);

	const Vector2& GetTarget() const;

	void SetTarget(const Vector2& target);

	const float GetTargetRadius() const;

	void SetTargetRadius(const float targetRad);

	void OutOfRange(std::function <void()> callback);

protected:

	Vector2 m_fleeTarget;
	float m_radiusOfTar = 1.0f;

	std::function<void()> m_outOfRangeFunc;

private:

};

