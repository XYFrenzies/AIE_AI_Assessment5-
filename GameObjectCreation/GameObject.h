#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Behaviour.h"

class Behaviour;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	//Default changes in the game
	virtual void Update(float deltaTime);
	virtual void Draw();

	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;
	const float& GetFriction() const;
	const float& GetMaxSpeed() const;


	Behaviour* GetBehaviour() const;
	//Sets the position of the object
	void SetPosition(const Vector2& pos);
	//Sets the velocity of the object
	void SetVelocity(const Vector2& vel);
	//Sets the friction of the object
	void SetFriction(const float& fric);

	void SetMaxSpeed(const float& speed);

	void SetBehaviour(Behaviour* beh);

	void ApplyForce(const Vector2& force);

	void Unload();

	//This is already in the raylib math libraries
	//Vector2 Vector2Add(Vector2 value1, Vector2 value2);

	//Vector2 Vector2Scale(Vector2 value1, float value2);

	//Vector2 Vector2Negate(Vector2 value1);
protected:
	Vector2 m_pos = {0, 0};//Position
	Vector2 m_vel = {0, 0};//Velocity
	Vector2 m_accel = {0, 0};//Acceleration
	float m_fric = 0.0f;//Friction

	float m_maxSpeed = 100;

	Behaviour* m_behaviour;
private:

};

