#pragma once
#include "../PixelEntity.h"

// Very basic pixel entity that walks in a random direction every frame

class RandomWalkEntity :
    public PixelEntity
{
    using PixelEntity::PixelEntity;
public:
    void do_step(); 
};

