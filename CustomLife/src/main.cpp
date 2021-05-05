#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "EntityFrame.h"
#include "PixelEntity.h"
#include "Entities/AvoidantEntity.h"
#include "Entities/RandomAvoidantEntity.h"
#include "Entities/RandomWalkEntity.h"
#include "Entities/PredatorPrey.h"
#include "Entities/SmartPredatorPrey.h"


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

void set_window_title(sf::RenderWindow &window, EntityFrame &frame) {
    std::ostringstream ss;
    int total = 0;
    int predator_count = 0;
    int prey_count = 0;
    for (auto ent : frame.entities) {
        predator_count += (ent->type_id == 2);
        prey_count += (ent->type_id == 3);
        total++;
    }
    ss << "Total creatures: " << total << " predators: " << predator_count << " prey: " << prey_count;
    std::string title = ss.str();
    window.setTitle(title);
}

int main()
{
    size_t width = 512;
    size_t height = 512;
    size_t total_pixels = width * height;

    sf::Uint8* pixel_array;

    EntityFrame frame(width, height);
    frame.toroid_grid = true;
    //frame.available_pixels = 256*16;
    sf::Vector2<int> pos;

    //AvoidantEntity* p1 = new AvoidantEntity(sf::Vector2<int>(0,100), sf::Color::White);
    //p1->add_to_frame(&frame);
    //AvoidantEntity* p2 = new AvoidantEntity(sf::Vector2<int>(511, 100), sf::Color::White);
    //p2->add_to_frame(&frame);

    /*p1->update_neighbours();
    for (auto ent : p1->neighbours) {
        std::cout << "Found neighbour at: (" << ent->pos.x << "," << ent->pos.y << ") \n";
    }*/

    // single prey:
    pos = sf::Vector2<int>(0, 0);
    Prey* p = new SmartPrey(pos, sf::Color::Green);
    p->add_to_frame(&frame);

     //Initialize a bunch of entities
    int num_prey = 256;
    int num_predator = 256;
    /*for (int i = 0; i < num_prey; i++) {
        pos = sf::Vector2<int>(rand() % width, rand() % height);
        Prey* p = new Prey(pos, sf::Color::Green);
        p->add_to_frame(&frame);
    }
    for (int i = 0; i < num_predator; i++) {
        pos = sf::Vector2<int>(rand() % width, rand() % height);
        Predator* p = new Predator(pos);
        p->add_to_frame(&frame);
    }*/

    /*int num_ent = 2048;
    for (int i = 0; i < num_ent; i++) {
        pos = sf::Vector2<int>(rand() % width, rand() % height);
        AvoidantEntity* p = new AvoidantEntity(pos, sf::Color::White);
        p->add_to_frame(&frame);
    }*/

    sf::Image pixel_image;

    sf::Texture pixel_texture;
    sf::Sprite pixel_sprite;

    sf::RenderWindow window(sf::VideoMode(width, height), "");
    //window.setFramerateLimit(120);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        frame.do_step();
        //check_overlap(&frame);
        pixel_array = frame.pixel_array;
        pixel_image.create(width, height, pixel_array);
        pixel_texture.loadFromImage(pixel_image);
        pixel_sprite.setTexture(pixel_texture, true);

        set_window_title(window, frame);
        window.clear();
        window.draw(pixel_sprite);
        window.display();
    }

    for (PixelEntity* p : frame.entities) {
        delete p;
    }

    return 0;
}
