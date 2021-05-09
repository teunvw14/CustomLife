#pragma once

#include <iostream>
#include "../EntityFrame.h"
#include "../PixelEntity.h"

// Check for overlapping entities
// Should only be used for debugging, causes extreme slowdown
void check_overlap(EntityFrame* frame) {
    for (PixelEntity* ent : frame->entities) {
        ent->update_neighbours();
        int neighbour_count = ent->neighbours.size();
        int max_neighbours = (2 * ent->neighbour_radius + 1) * (2 * ent->neighbour_radius + 1);
        if (neighbour_count > max_neighbours) {
            std::cout << "Something is wrong here: neighbour_count = " << neighbour_count << " max_neighbours = " << max_neighbours << "\n";
        }
    }
}
