#pragma once
#include "AvoidantEntity.h"
class RandomAvoidantEntity :
    public AvoidantEntity
{
    using AvoidantEntity::AvoidantEntity;
public:
    void do_step();
};

