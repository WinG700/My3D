#pragma once
#include <set>
#include "Actor.h"
#include "Camera.h"
class UWorld
{
public:
	UWorld();
	~UWorld();
	UWorld(Camera* In_Cam);
	set<Actor*> Actors;
	Camera* Cam;
};

