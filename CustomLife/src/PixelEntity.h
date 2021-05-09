#pragma once
#include <SFML/Graphics.hpp>

class EntityFrame;
class PixelEntity
{
public:
	EntityFrame* frame; // The frame within which a pixel exists
	unsigned int neighbour_radius; // Radius within which other pixels are considered neighbours
	std::vector<PixelEntity*> neighbours; // A vector containing the neighbours of the pixel
	sf::Vector2<int> pos; // Position of the pixel within its frame
	sf::Color color;
	int type_id;
	
	PixelEntity(sf::Vector2<int> pos);
	PixelEntity(sf::Color color);
	PixelEntity(sf::Vector2<int> pos, sf::Color color);

	virtual void do_step() = 0 ; // Should be defined in inheriting classes
	void add_to_frame(EntityFrame* frame);

	// Methods related to pixel movement
	void move_to_unsafe(sf::Vector2<int> pos);
	void move_to(sf::Vector2<int> pos);
	void move_up();
	void move_right();
	void move_left();
	void move_down();

	// Utility functions
	void update_neighbours();
};
