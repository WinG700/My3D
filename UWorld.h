#pragma once
#include <vector>
#include "Actor.h"
#include "Camera.h"
#include "Rasterization.h"
class UWorld
{
public:
	UWorld();
	~UWorld();
	UWorld(Camera* In_Cam);
	vector<Actor*> Actors;
	Camera* Cam;
	Rasterization* rasterization;
	void Tick(double DeltaSecond);
};

