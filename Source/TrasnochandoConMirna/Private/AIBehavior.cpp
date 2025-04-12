#include "AIBehavior.h"

UAIBehavior::UAIBehavior()
{
	PrimaryComponentTick.bCanEverTick = false;

	PatrolType = EPatrolNavigationType::Loop;
}
