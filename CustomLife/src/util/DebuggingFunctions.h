#pragma once

#include <iostream>
#include "../EntityFrame.h"
#include "../PixelEntity.h"

// Check for overlapping entities
// Should only be used for debugging, causes extreme slowdown
void check_overlap(EntityFrame* frame) {
    for (PixelEntity* ent_first : frame->entities) {
        size_t count = 0;
        for (PixelEntity* ent_second : frame->entities) {
            if (count > 0 && ent_first->pos == ent_second->pos) {
                count++;
                std::cout << "Something is going terribly wrong!!" << std::endl;
            }
        }
    }
}
