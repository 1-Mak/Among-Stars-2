#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define ICON_WIDTH 100
#define ICON_HEIGHT 100
#define LOGO_BACK_WIDTH 1800
#define LOGO_BACK_HEIGHT 200
#define LOGO_POS_X (WIN_WIDTH - LOGO_BACK_WIDTH)/2
#define LOGO_POS_Y 20
#define HEALTH_POS_X 100
#define HEALTH_POS_Y 1000
#define SPACE_WIDTH 1920
#define SPACE_HEIGHT WIN_HEIGHT
#define WORLD_SPEED 2000
#define PLAYER_SPEED 1000
#define METEOR_SPEED 1000
#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 80
#define MOVE_PLAYER 0.3
#define SCALE 1
#define METEORS 70
#define MAX_HEALTH 10
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include "Full.h"
using namespace sf;


struct Animation {
    int frame = 0;
    int frame1 = 0;
    int step = 100;
    int step1 = 100;
};

void player_move(RectangleShape& player_rect, Vector2f& move_player);
void correct(Full& can, int i, Obstacle * meteor, int num_meteor);
void correct_full(Full& can, Obstacle* meteor, int num_meteor);
std::string int_to_str(int num);
