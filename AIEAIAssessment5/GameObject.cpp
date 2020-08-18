#include "GameObject.h"

GameObject::GameObject(): m_pos(), m_vel(), m_accel(), m_fric(), m_behaviour()
{

}

GameObject::~GameObject()
{
	delete m_behaviour;
	m_behaviour = nullptr;
	delete GetBehaviour();

	for (auto node : m_nearbyNodes)
	{
		delete node;
	}
	m_nearbyNodes.clear();
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

	if (Vector2Length(m_vel) > 0) {
		m_facingDir = Vector2Normalize(m_vel);
	}

}

void GameObject::Draw()
{
	if (m_behaviour != nullptr)
		m_behaviour->Draw(this);

	Vector2 lineDir = Vector2Add(m_pos, m_vel);//Draws a directional line for the player

	if (IsKeyDown(KEY_TAB))
	{
		DrawCircle(m_pos.x, m_pos.y, m_outtaRadius, { 0, 255, 0, 100 });
		DrawCircle(m_pos.x, m_pos.y, m_innerRadius, { 100, 255, 100, 100 });
		DrawCircle(m_pos.x, m_pos.y, 8, RED);//Creates the player

		DrawLine(m_pos.x, m_pos.y, lineDir.x, lineDir.y, RED); //Creates the line
	}

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
const float& GameObject::GetMaxSpeed() const
{
	return m_maxSpeed;
	// TODO: insert return statement here
}
const float& GameObject::GetInnerRadius() const
{
	return m_innerRadius;
	// TODO: insert return statement here
}
const float& GameObject::GetOuttaRadius() const
{
	return m_outtaRadius;
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
void GameObject::SetMaxSpeed(const float& speed)
{
	m_maxSpeed = speed;
}
void GameObject::SetInnerRadius(const float& inRad)
{
	m_innerRadius = inRad;
}
void GameObject::SetOuttaRadius(const float& outRad)
{
	m_outtaRadius = outRad;
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
