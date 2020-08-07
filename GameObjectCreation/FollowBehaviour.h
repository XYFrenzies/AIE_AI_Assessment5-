#pragma once
#include "Behaviour.h"
#include "raymath.h"

class Graph2D;

class FollowBehaviour : public Behaviour
{
//Look into how to make this class. Write down some notes
public:
	FollowBehaviour();
	virtual ~FollowBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);

	//const Graph2D GetTarget();

	//void SetTarget(const Graph2D* target);

	//const float GetTargetRadius() const;

	//void SetTargetRadius(const float targetRad);

protected:

	float m_radius = 1.0f;
	Graph2D* m_graph;
private:

};

