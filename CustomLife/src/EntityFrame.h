#pragma once
#include <random> 
#include <SFML/Graphics.hpp>

class PixelEntity;
class EntityFrame
{
private:
	std::random_device rand_dev;
    std::mt19937 random_direction_generator;
    std::uniform_int_distribution<int> unif_distr;
	void setup_pixel_array(sf::Color background_color = sf::Color::Black);
public:
	size_t width, height;
	std::vector<PixelEntity*> entities;
	std::vector<PixelEntity*> entity_grid;
	bool is_full;

	// This flag sets the movement to be on a toroid. This means that when a
	// PixelEntity walks across a border, it ends up on the "opposite" side 
	// of the plane instead of being blocked;
	bool toroid_grid;
	size_t available_pixels;
	sf::Uint8* pixel_array;

	EntityFrame();
	~EntityFrame();
	EntityFrame(size_t w, size_t h);

	void do_step();
	PixelEntity* at(sf::Vector2<int> pos);
	PixelEntity* at_unsafe(sf::Vector2<int> pos);
	void move_entity(PixelEntity* pixel_to_move, sf::Vector2<int> to);
	bool grid_pos_safe(sf::Vector2<int> pos);
	bool pos_within_bounds(sf::Vector2<int> pos);
	bool pos_free_unsafe(sf::Vector2<int> pos);
	sf::Vector2<int> pos_toroid_adjust(sf::Vector2<int> pos);
	int get_random_direction();
	bool add_entity(PixelEntity* ent);
	void destroy(PixelEntity* ent);
	void set_pixel(int position_in_grid, sf::Color color);
	void set_pixel(sf::Vector2<int> vec_pos, sf::Color color);
};



