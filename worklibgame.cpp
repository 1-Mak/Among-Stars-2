#include "worklibgame.h"

void player_move(RectangleShape& player_rect, Vector2f& move_player)
{
    player_rect.move(move_player);
    Vector2f position = player_rect.getPosition();

    if (position.x > WIN_WIDTH - PLAYER_WIDTH) player_rect.setPosition(WIN_WIDTH - PLAYER_WIDTH, position.y);
    if (position.x < 0) player_rect.setPosition(0, position.y);
    if (position.y > WIN_HEIGHT - PLAYER_HEIGHT) player_rect.setPosition(position.x, WIN_HEIGHT - PLAYER_HEIGHT);
    if (position.y < LOGO_BACK_HEIGHT) player_rect.setPosition(position.x, LOGO_BACK_HEIGHT);
    if ((position.x > WIN_WIDTH) && (position.y < LOGO_BACK_HEIGHT)) player_rect.setPosition(WIN_WIDTH, LOGO_BACK_HEIGHT);
    if ((position.x > WIN_WIDTH) && (position.y > WIN_HEIGHT)) player_rect.setPosition(WIN_WIDTH, WIN_HEIGHT);
    if ((position.x < 0) && (position.y < LOGO_BACK_HEIGHT)) player_rect.setPosition(0, LOGO_BACK_HEIGHT);
    if ((position.x < 0) && (position.y > WIN_HEIGHT)) player_rect.setPosition(0, WIN_HEIGHT);
}

void correct(Full& can, int i, Obstacle* meteor, int num_meteor)
{
    for (int i1 = 0; i1 < num_meteor; i1++)
    {
        if (i1 != i) {
            if (meteor[i1].collision(meteor[i].get_obs_bounds()))
            {
                meteor[i].restart();
                correct(can, i, meteor, num_meteor);
                break;
            }
        }

    }
    if (can.collision(meteor[i].get_obs_bounds())) 
    { 
    meteor[i].restart();
    correct(can, i, meteor, num_meteor); 
    }
}
void correct_full(Full & can, Obstacle * meteor, int num_meteor)
    {
        for (int i1 = 0; i1 < num_meteor; i1++)
        {
            if (meteor[i1].collision(can.get_obs_bounds()))
            {
                can.restart();
                correct_full(can, meteor, num_meteor); break;
            }
        }
    }
std::string int_to_str(int num) {
    std::ostringstream text_string;
    text_string << num;
    return text_string.str();
}