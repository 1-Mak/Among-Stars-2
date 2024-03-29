#include "Full.h"

Full::Full(String name, int x, int y)

{
	obs_texture.loadFromFile(name);
	obs_sprite.setTexture(obs_texture);
	obs_sprite.setTextureRect(IntRect(0, 0, x, y));
	int scal = 1000 / x;
	obs_sprite.setScale(0.05 * scal, 0.05 * scal);
	restart();
}

Full::~Full()
{
}

void Full::restart()
{
	newborn = true;
	float x = static_cast<float>(rand() % 1920 + 1920);
	float y = static_cast<float>(rand() % 1080 + 200);

	obs_sprite.setPosition(Vector2f(x, y));
	pos_bonus = obs_sprite.getPosition();
}
