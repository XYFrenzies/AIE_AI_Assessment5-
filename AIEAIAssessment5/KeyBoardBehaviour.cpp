#include "KeyBoardBehaviour.h"
#include "raylib.h"
#include "GameObject.h"
KeyBoardBehaviour::KeyBoardBehaviour(): Behaviour()
{
	m_upKey = KEY_W;//Default for the player moving up using w
	m_downKey = KEY_S;//Default for the player moving down using s
	m_leftKey = KEY_A;//Default for the player moving left using a
	m_rightKey = KEY_D;//Default for the player moving right using d
	m_moveForce = 100;//Default for the player moving with 100 force
}

KeyBoardBehaviour::KeyBoardBehaviour(int up, int down, int left, int right, float move): 
	m_upKey(up), //Sets the input as the up key
	m_downKey(down),//Sets the input as the down key
	m_leftKey(left),//Sets the input as the left key
	m_rightKey(right),//Sets the input as the right key
	m_moveForce(move)//Sets the input to moving
{
}

KeyBoardBehaviour::~KeyBoardBehaviour()
{
}

void KeyBoardBehaviour::Update(GameObject* obj, float deltaTime)
{
	//Checks for input
	if (IsKeyDown(m_leftKey)) obj->ApplyForce({ -m_moveForce, 0 });//Left key
	if (IsKeyDown(m_rightKey)) obj->ApplyForce({ m_moveForce, 0 });//Right key
	if (IsKeyDown(m_upKey)) obj->ApplyForce({ 0,  -m_moveForce });// Up key
	if (IsKeyDown(m_downKey)) obj->ApplyForce({ 0,m_moveForce });// Down key
}
