#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
class Obstacle
{
public:
	Obstacle();
	~Obstacle();

	void move(float& time);
	void draw(RenderWindow& window);
	void animation();
	bool collision(FloatRect obj);
	virtual void restart();
	FloatRect get_obs_bounds();
	bool newborn;
	Vector2f get_bonus_pos()
	{
		return pos_bonus;
	}
protected:
	Sprite obs_sprite;
	Texture obs_texture;
	Vector2f pos_bonus;
private:
	

	int pix_arr_x[5]{3,73,135,198,262};
	int pix_arr_y[6]{3, 68, 132, 200,265,325};


	int x, y = 0;
	int s = 0;
};

