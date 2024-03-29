#include "Obstacle.h"
#include <cstdlib>

#define OBSTACLE_SIZE 13
#define OBSTACLE_X 1920 
#define OBSTACLE_Y 1080
#define SPEED_METEOR -0.5


Obstacle::Obstacle()
{
	obs_texture.loadFromFile("Sprites/obstacle.png");
	obs_sprite.setTexture(obs_texture);
	obs_sprite.setTextureRect(IntRect(262,325,55,50));
	restart();
}

Obstacle::~Obstacle()
{

}

void Obstacle::move(float& time)
{
	newborn = false;
	obs_sprite.move(static_cast<float>(SPEED_METEOR*time), 0);
	pos_bonus = obs_sprite.getPosition();
	if (obs_sprite.getPosition().x < -60) restart();
	

}

void Obstacle::draw(RenderWindow& window)
{
	window.draw(obs_sprite);
}

void Obstacle::animation()
{
	if (s > 0) {
		obs_sprite.setTextureRect(IntRect(pix_arr_x[x], pix_arr_y[y], 50, 45));
		x += s;
		if (x > 4) {
			x = 0;
			y++;
			if (y > 5) {
				y = 0;
			}
		}
	}
}

bool Obstacle::collision(FloatRect obj)
{

	if (obs_sprite.getGlobalBounds().intersects(obj)) {
		return true;
	}

	return false;
}

void Obstacle::restart()
{
	newborn = true;
	float rand = static_cast<float>((std::rand() % OBSTACLE_SIZE + 5) / 10);
	float rand1 = static_cast<float>((std::rand() % OBSTACLE_SIZE + 5) / 10);
	float x1 = static_cast<float>(std::rand() % OBSTACLE_X + 2000);
	float y1 = static_cast<float>(std::rand() % OBSTACLE_Y + 225);
	obs_sprite.setPosition(Vector2f(x1, y1));
	obs_sprite.setScale(rand, rand1);
	x = std::rand() % 4;
	y = std::rand() % 5;
	s = std::rand() % 2;
	pos_bonus = obs_sprite.getPosition();

}
 FloatRect Obstacle::get_obs_bounds()
{
	return obs_sprite.getGlobalBounds();
}
