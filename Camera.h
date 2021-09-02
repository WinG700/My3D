#pragma once
#include "Actor.h"
class Camera :
    public Actor
{
public:
    Camera();
    ~Camera();
    Camera(const FTransfrom& trans);
};

