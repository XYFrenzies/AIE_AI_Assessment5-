#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Behaviour.h"
#include "Graph2D.h"

class Behaviour;
class GameObject
{
public:
	GameObject();//Constructor
	virtual ~GameObject();//Virtual Deconstructor

	//Default changes in the game
	virtual void Update(float deltaTime);
	virtual void Draw();

	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;
	const float& GetFriction() const;
	const float& GetMaxSpeed() const;
	const float& GetInnerRadius() const;
	const float& GetOuttaRadius() const;
	
	Behaviour* GetBehaviour() const;
	//Sets the position of the object
	void SetPosition(const Vector2& pos);
	//Sets the velocity of the object
	void SetVelocity(const Vector2& vel);
	//Sets the friction of the object
	void SetFriction(const float& fric);

	void SetMaxSpeed(const float& speed);

	void SetInnerRadius(const float& inRad);

	void SetOuttaRadius(const float& outRad);


	void SetBehaviour(Behaviour* beh);

	void ApplyForce(const Vector2& force);

protected:
	Vector2 m_pos = {0, 0};//Position
	Vector2 m_vel = {0, 0};//Velocity
	Vector2 m_accel = {0, 0};//Acceleration
	Vector2 m_facingDir = { 0, -1 };
	float m_fric = 0.0f;//Friction

	float m_maxSpeed = 100;//MaxSpeed
	float m_innerRadius = 35;//The inner radius of the agent
	float m_outtaRadius = 100;//The outta radius of the agent

	Behaviour* m_behaviour;//Instance in memory of a behaviour

	std::vector<Graph2D::Node*> m_nearbyNodes;//A vector of nodes
private:

};

