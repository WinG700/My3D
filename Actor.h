#pragma once
#include "Matrix.h"

class Actor
{
public:
	FTransfrom ActorTransform;
	Actor();
	Actor(const FTransfrom &Trans);
};

