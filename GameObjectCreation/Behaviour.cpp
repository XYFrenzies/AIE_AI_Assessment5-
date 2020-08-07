#include "Behaviour.h"
#include "GameObject.h"
#include <iostream>
Behaviour::Behaviour()
{
}

Behaviour::~Behaviour()
{
}

void Behaviour::Update(GameObject* obj, float deltaTime)
{
	std::cout << "Updating" << std::endl;
}

void Behaviour::Draw(GameObject* obj)
{
}
