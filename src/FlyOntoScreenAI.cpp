#include "FlyOntoScreenAI.h"

FlyOntoScreenAI::FlyOntoScreenAI(){/*DANGER! Do not use!*/}

FlyOntoScreenAI::~FlyOntoScreenAI()
{
}

void FlyOntoScreenAI::PrimaryFunction()
{
	if (!atTarget)
	{
		parent->setPosition(parent->getPosition() + entrySpeed);
		if (!backTarget && parent->getPosition().x <= target.x && parent->getPosition().y == target.y) {
			atTarget = true;
		}
		else if (backTarget && parent->getPosition().x >= target.x && ((entrySpeed.y > 0 && parent->getPosition().y >= target.y) || (entrySpeed.y < 0 && parent->getPosition().y <= target.y))) {
			atTarget = true;
		}
	}
	else { SecondaryFunction(); }
}

void FlyOntoScreenAI::SecondaryFunction()
{
	/*Leave this blank*/
}

glm::vec2 FlyOntoScreenAI::GetSpeed()
{
	return atTarget ? speed : glm::vec2{0,0};
}

bool FlyOntoScreenAI::isAtTarget()
{
	return atTarget;
}

int FlyOntoScreenAI::getRotation()
{
	return rotation;
}
