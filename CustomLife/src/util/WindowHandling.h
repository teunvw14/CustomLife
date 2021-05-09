#pragma once

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "../EntityFrame.h"


void set_window_title(sf::RenderWindow& window, EntityFrame& frame) {
    // Set the title to display how many of each type of creature exists.
    std::ostringstream ss;
    int total = 0;
    int predator_count = 0;
    int prey_count = 0;
    std::string frame_full_message = (frame.available_pixels == 0 ? " (frame full)" : "");
    for (auto ent : frame.entities) {
        predator_count += (ent->type_id == 2);
        prey_count += (ent->type_id == 3);
        total++;
    }
    ss << "Total creatures: " << total  << frame_full_message << " predators: " << predator_count << " prey: " << prey_count;
    std::string title = ss.str();
    window.setTitle(title);
}
