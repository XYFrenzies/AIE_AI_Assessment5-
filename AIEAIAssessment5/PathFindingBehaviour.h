#pragma once
#include "Behaviour.h"
#include "raymath.h"

#include "Graph2DEditor.h"

class PathFindingBehaviour : public Behaviour
{
public:
	PathFindingBehaviour();
	virtual ~PathFindingBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);

	const Vector2& GetTarget() const;

	void SetTarget(const Vector2& target);

	const float GetTargetRadius() const;

	void SetTargetRadius(const float targetRad);

	void AddPath(std::vector<Vector2>& path);

protected:
private:

	Graph2DEditor m_pathFind; // stores the path
	Vector2 m_target;
	float m_targetRadi = 1.0f;

	std::function<void()> m_onArriveFunc;

	bool pathAdded = false;
	std::vector<Vector2> m_targetNodes;
};

