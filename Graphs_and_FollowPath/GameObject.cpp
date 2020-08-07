#include "GameObject.h"

GameObject::GameObject(): m_pos(), m_vel(), m_accel(), m_fric(), m_behaviour()
{

}

GameObject::~GameObject()
{
	delete m_behaviour;
	m_behaviour = nullptr;
	delete GetBehaviour();
}

void GameObject::Update(float deltaTime)
{
	//If the behaviour exists
	if(m_behaviour)
		m_behaviour->Update(this, deltaTime);

	//Applies force as a result of the reduction of the velocity and the friction
	ApplyForce(Vector2Scale(Vector2Negate(m_vel), m_fric));
	//new Velocity is the addition of the velocity + the scaling of the acceleration and delta time.
	m_vel = Vector2Add(m_vel, Vector2Scale(m_accel, deltaTime));
	//new Position is the addition of the position + the scaling of the velocity and delta time.
	m_pos = Vector2Add(m_pos, Vector2Scale(m_vel, deltaTime));

	//clear the acceleration "Sets it to zero"
	m_accel = Vector2Zero();
}

void GameObject::Draw()
{
	if (m_behaviour != nullptr)
		m_behaviour->Draw(this);

	Vector2 lineDir = Vector2Add(m_pos, m_vel);//Draws a directional line for the player

	DrawCircle(m_pos.x, m_pos.y, 8, RED);//Creates the player

	DrawLine(m_pos.x, m_pos.y, lineDir.x, lineDir.y, RED); //Creates the line
}
//Gets the position of the player
const Vector2& GameObject::GetPosition() const
{

	return m_pos;
	// TODO: insert return statement here
}
//Gets the velocity of the player
const Vector2& GameObject::GetVelocity() const
{
	// TODO: insert return statement here
	return m_vel;
}
//Gets the friction of the player
const float& GameObject::GetFriction() const
{
	return m_fric;
	// TODO: insert return statement here
}
//Gets the behaviour of the player
Behaviour* GameObject::GetBehaviour() const
{
	return nullptr;
}
//Sets the position of the player
void GameObject::SetPosition(const Vector2& pos)
{
	m_pos = pos;
}
//Sets the velocity of the player
void GameObject::SetVelocity(const Vector2& vel)
{
	m_vel = vel;
}
//Sets the friction of the player
void GameObject::SetFriction(const float& fric)
{
	m_fric = fric;
}
//Sets a certain behaviour
void GameObject::SetBehaviour(Behaviour* beh)
{
	m_behaviour = beh;
}
//Adds the force to the acceleration to make it go faster over time.
void GameObject::ApplyForce(const Vector2& force)
{
	m_accel = Vector2Add(m_accel, force);
}
//Deletes values to prevent memory leaks

//These are already inbuilt from raylib but want to keep them to show what is happening in the background

//Vector2 GameObject::Vector2Add(Vector2 value1, Vector2 value2)
//{
//	Vector2 newValue; 
//	newValue.x = value1.x + value2.x;
//	newValue.y = value1.y + value2.y;
//	return newValue;
//}
//
//Vector2 GameObject::Vector2Scale(Vector2 value1, float value2)
//{
//	Vector2 newValue;
//	newValue.x = value1.x * value2;
//	newValue.y = value1.y * value2;
//	
//
//	return newValue;
//}

//Vector2 GameObject::Vector2Negate(Vector2 value1)
//{
//	Vector2 newValue;
//	newValue.x = value1.x --;
//	newValue.y = value1.y--;
//
//	return newValue;
//}
