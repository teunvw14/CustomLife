#pragma once
#include <iostream>
#include <random>
#include "../PixelEntity.h"
class AvoidantEntity :
    public PixelEntity
{
    using PixelEntity::PixelEntity;
public:
    void do_step();
};

