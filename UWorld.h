#pragma once
#include <set>
#include "Actor.h"
#include "Camera.h"
#include "Rasterization.h"
class UWorld
{
public:
	UWorld();
	~UWorld();
	UWorld(Camera* In_Cam);
	set<Actor*> Actors;
	Camera* Cam;
	Rasterization* rasterization;
	void Tick(float DeltaSecond);
};

