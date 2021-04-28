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
	size_t available_pixels;
	sf::Uint8* pixel_array;

	EntityFrame();
	~EntityFrame();
	EntityFrame(size_t w, size_t h);

	void do_step();
	PixelEntity* at(sf::Vector2<int> pos);
	void move_entity(PixelEntity* pixel_to_move, sf::Vector2<int> to);
	int get_random_direction();
	bool add_entity(PixelEntity* ent);
	void destroy(PixelEntity* ent);
	void set_pixel(int position_in_grid, sf::Color color);
	void set_pixel(sf::Vector2<int> vec_pos, sf::Color color);
};


// This is a duplicate of the EntityFrame, except for the fact that movement is on
// a toroid. This means that when an PixelEntity walks across a border, it ends up on the 
// "opposite" side of the plane. 
class ToroidEntityFrame : public EntityFrame {
	using EntityFrame::EntityFrame;
public:
	void move_entity(PixelEntity* pixel_to_move, sf::Vector2<int> to);
};