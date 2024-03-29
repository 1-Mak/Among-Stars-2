#include "worklibgame.h"


void InitText(Text& text, float x, float y, String str, int size = 60, Color text_color = Color::White, int bord = 0, Color bord_color = Color::Black) {
    text.setCharacterSize(size);
    text.setPosition(x,y);
    text.setString(str);
    text.setFillColor(text_color);
    text.setOutlineThickness(bord);
    text.setOutlineColor(bord_color);
}




using namespace sf;

int main()
{


    srand(time(NULL));
    Vector2f position;
    Vector2f move_player;
    Clock clock;
    Clock clock_anim;
    Clock clock_obs;
    Clock clock_text;
    float time;
    float time_player;
    float time_background;
    float time_obs;
    int array_anim[3]{ 9,59,103 };
    int frame = 3;
    int step = -1;
    bool end = false;
    bool pause = false;
    int delay = 0;
    double tmp_fuel = 0;
    int fuel = 100;
    Text text_fuel, plus_fuel, text_pause, end_game, text_earth, text_newStar;
    Font font;
    if (!font.loadFromFile("Fonts/Metro.otf")) return -5;
    int health = 10;
    RenderWindow win;
    win.create(VideoMode::getDesktopMode(), L"Among Stars 2", Style::Fullscreen);
    win.setMouseCursorVisible(false);


    text_fuel.setFont(font);
    text_fuel.setFillColor(Color::Green);
    text_fuel.setCharacterSize(30);
    text_fuel.setPosition(100, 1000 );

    plus_fuel.setFont(font);
    plus_fuel.setFillColor(Color::White);
    plus_fuel.setCharacterSize(30);

    end_game.setFont(font);
    end_game.setFillColor(Color::White);
    end_game.setCharacterSize(50);
    end_game.setString(L"GAME OVER");
    end_game.setPosition(WIN_WIDTH/2 - 250, 500);

    text_pause.setFont(font);
    text_pause.setFillColor(Color::White);
    text_pause.setCharacterSize(50);
    text_pause.setString(L"P A U S E");
    text_pause.setPosition(WIN_WIDTH / 2 - 250, 500);

    text_earth.setFont(font);
    text_earth.setFillColor(Color::Green);
    text_earth.setCharacterSize(30);
    text_earth.setString(L"EARTH");
    text_earth.setPosition(400, 980);

    text_newStar.setFont(font);
    text_newStar.setFillColor(Color::Red);
    text_newStar.setCharacterSize(30);
    text_newStar.setString(L"NEW STAR");
    text_newStar.setPosition(750, 980);

    float win_width = VideoMode::getDesktopMode().width;
    float win_height = VideoMode::getDesktopMode().height;

    bool music = false;

    Music game_music;

    if (!game_music.openFromFile("Music/GameMusic.mp3"))
    {
        return -6;
    }
   
    game_music.setLoop(true);
    game_music.setVolume(15);

    Sound sound_fal;
    Sound sound_1;
    Sound sound_vic;

    SoundBuffer fal, s1, vic;

    fal.loadFromFile("Music/faled1.wav");
    sound_fal.setBuffer(fal);
    sound_fal.setVolume(15);
    s1.loadFromFile("Music/bonus.wav");
    sound_1.setBuffer(s1);
    sound_1.setVolume(15);
    vic.loadFromFile("Music/victory.wav");
    sound_vic.setBuffer(vic);
    sound_vic.setVolume(15);


    CircleShape circle(5.f);
    circle.setFillColor(Color::Red);
    circle.setOutlineThickness(3.f);
    circle.setOutlineColor(Color::Black);
    circle.setPosition(500, 1017);


    RectangleShape radar_line(Vector2f(400, 5));
    radar_line.setFillColor(Color::Black);
    radar_line.setPosition(500, 1020);

    Image icon;
    if (!icon.loadFromFile("Sprites/icon.png"))
    {
        return -1;
    }
    win.setIcon(ICON_WIDTH, ICON_HEIGHT, icon.getPixelsPtr());


    Texture Game_logo;

    if (!Game_logo.loadFromFile("Sprites/Among_Stars_2.png"))
    {
        return -2;
    }
    RectangleShape Game_rect(Vector2f(LOGO_BACK_WIDTH, LOGO_BACK_HEIGHT));
    Game_rect.setTexture(&Game_logo);
    Game_rect.setPosition(LOGO_POS_X, LOGO_POS_Y);
    Texture Space_background;
    if (!Space_background.loadFromFile("Sprites/background.png"))
    {
        return -3;
    }
    RectangleShape Space_rect(Vector2f(SPACE_WIDTH, SPACE_HEIGHT));
    Space_rect.setTexture(&Space_background);

    RectangleShape Space_rect2(Vector2f(SPACE_WIDTH, SPACE_HEIGHT));
    Space_rect2.setTexture(&Space_background);
    Space_rect2.setPosition(win_width, 0);

    Texture spaceship_player;

    if (!spaceship_player.loadFromFile("Sprites/playeranim.png"))
    {
        return -4;
    }

    Texture player;
    player.loadFromFile("Sprites/player_ship.png");
    RectangleShape player_rect(Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
    player_rect.setTexture(&player);
    player_rect.setPosition(Vector2f(50, 500));


    Texture fire;
    fire.loadFromFile("Sprites/animation.png");
    Sprite fire_sprite;
    fire_sprite.setTexture(fire);
    fire_sprite.setTextureRect(IntRect(0, 103, 85, 43));





    Animation end_anim;
    end_anim.frame = 5;
    end_anim.frame1 = 15;
    Texture end_text;

    end_text.loadFromFile("Sprites/boom.png");
    Sprite destr;
    destr.setTexture(end_text);
    destr.setTextureRect(IntRect(5, 15, 95, 80));
    destr.scale(SCALE, SCALE);

    const int num_meteors = METEORS;
    Obstacle meteor[num_meteors];


    Full can("Sprites/galon.png", 1000, 1000);



    RectangleShape health_bar_outline(Vector2f(250, 20));
    health_bar_outline.setFillColor(Color(0, 0, 0, 0));
    health_bar_outline.setPosition(Vector2f(HEALTH_POS_X, HEALTH_POS_Y));
    health_bar_outline.setOutlineThickness(5);
    health_bar_outline.setOutlineColor(Color::Black);

    while (win.isOpen())

    {

        Event event;
        RectangleShape health_bar(Vector2f((health / MAX_HEALTH) * 250, 20));
        health_bar.setFillColor(Color::Red);
        health_bar.setPosition(Vector2f(HEALTH_POS_X, HEALTH_POS_Y));
        time = clock.getElapsedTime().asMicroseconds();
        time_player = time / PLAYER_SPEED;
        time_background = time / WORLD_SPEED;
        time_obs = time / METEOR_SPEED;
        clock.restart();

        while (win.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::KeyPressed:
                if (event.key.code == Keyboard::F2) {
                    pause = !pause;

                }
                if (event.key.code == Keyboard::F3) {
                    win.close();

                }
                if (event.key.code == Keyboard::F1) {
                    music = !music;
                    if (music) {
                        game_music.play();
                    }
                    else {
                        game_music.stop();
                    }
                }

                if (event.key.code == Keyboard::S) {

                    if (fuel != 0) {
                        move_player.y = MOVE_PLAYER * time_player;
                        fuel--;
                    }
                }
                if (event.key.code == Keyboard::W) {
                    if (fuel != 0) {
                        move_player.y = -MOVE_PLAYER * time_player;
                        fuel--;
                    }

                }
                if (event.key.code == Keyboard::A) {
                    if (fuel != 0) {
                        move_player.x = -MOVE_PLAYER * time_player;
                        fuel--;
                    }
                }

                if (event.key.code == Keyboard::D) {
                    if (fuel != 0) {
                        move_player.x = MOVE_PLAYER * time_player;
                        fuel--;
                    }
                }

                break;
            case Event::KeyReleased:
                if (event.key.code == Keyboard::S) {
                    move_player.y = 0;

                }
                if (event.key.code == Keyboard::W) {
                    move_player.y = 0;

                }
                if (event.key.code == Keyboard::A) {
                    move_player.x = 0;
                }

                if (event.key.code == Keyboard::D) {
                    move_player.x = 0;
                }

                break;
            default:
                break;
            }

            if (event.type == Event::Closed)
                win.close();
        }
        if (pause == false) {
            if (circle.getPosition().x <= 900) {




                if (end == true) {
                    if (clock_obs.getElapsedTime() > milliseconds(100))
                    {
                        clock_obs.restart();
                        end_anim.frame += end_anim.step;
                        if (end_anim.frame > 405)
                        {
                            end_anim.frame1 += end_anim.step1;
                            end_anim.frame = 5;
                        }
                        if (end_anim.frame1 > 415)
                        {

                            end = false;
                            player_rect.setPosition(Vector2f(80, 380));
                            for (int i = 0; i < num_meteors; i++) {
                                meteor[i].restart();
                            }
                            can.restart();
                            circle.setPosition(500, 1017);
                            end_anim.frame = 5;
                            end_anim.frame1 = 15;
                            fuel = 100;
                        }
                        else
                        {
                            destr.setTextureRect(IntRect(end_anim.frame, end_anim.frame1, 95, 80));
                        }
                    }
                }
                else {



                    if (clock_anim.getElapsedTime() > milliseconds(100))
                    {
                        clock_anim.restart();
                        frame += step;
                        fire_sprite.setTextureRect(IntRect(0, array_anim[frame], 85, 43));
                        if (frame == 0) {
                            step = 1;
                        }
                        if (frame == 2)
                        {
                            step = -1;
                        }
                    }
                    fire_sprite.setPosition(Vector2f(player_rect.getPosition().x - 87, player_rect.getPosition().y + 21));
                    if (clock_obs.getElapsedTime() > milliseconds(80)) {
                        clock_obs.restart();
                        for (int i = 0; i < num_meteors; i++) {
                            meteor[i].animation();
                        }
                        circle.move(1, 0);
                    }
                    
                    if (clock_text.getElapsedTime() > milliseconds(80)) {
                        clock_text.restart();
                        if (delay > 0) {
                            delay--;
                            plus_fuel.move(0, -1);
                        }
                    }

                    Space_rect.move(-0.2 * time_background, 0);
                    position = Space_rect.getPosition();
                    if (position.x < -win_width) Space_rect.setPosition(win_width, position.y);

                    Space_rect2.move(-0.2 * time_background, 0);
                    position = Space_rect2.getPosition();
                    if (position.x < -win_width) Space_rect2.setPosition(win_width, position.y);

                    player_move(player_rect, move_player);

                    for (int i = 0; i < num_meteors; i++) {
                        if (meteor[i].newborn) {
                            correct(can, i, meteor, num_meteors);
                        }
                        meteor[i].move(time_obs);
                        if (meteor[i].collision(player_rect.getGlobalBounds())) {
                            sound_fal.play();
                            end = true;
                            destr.setPosition(player_rect.getPosition().x, player_rect.getPosition().y);
                            break;


                        }

                    }
                    if (can.newborn) {
                        correct_full(can, meteor, num_meteors);

                    }
                    can.move(time_obs);

                    if (can.collision(player_rect.getGlobalBounds())) {
                        tmp_fuel = 10 + rand() % 90;
                        fuel += tmp_fuel;
                        sound_1.play();
                        plus_fuel.setString(int_to_str(tmp_fuel));

                        plus_fuel.setPosition(can.get_bonus_pos().x, can.get_bonus_pos().y);
                        delay = 40;
                        can.restart();
                    }
                    if (fuel >= 100) {
                        text_fuel.setFillColor(Color::Green);
                    }
                    if (fuel < 100 && fuel >= 50) {
                        text_fuel.setFillColor(Color::Yellow);
                    }
                    if (fuel < 50) {
                        text_fuel.setFillColor(Color::Red);
                    }
                    text_fuel.setString(int_to_str(fuel) + L" tons");

                }
                win.clear();

                win.draw(Space_rect2);
                win.draw(Space_rect);
                win.draw(Game_rect);
                if (end == true) {
                    win.draw(destr);
                }
                else {
                    win.draw(player_rect);
                    win.draw(fire_sprite);
                }
                for (int i = 0; i < num_meteors; i++) {
                    meteor[i].draw(win);
                }
                can.draw(win);
                win.draw(text_fuel);

                if (delay > 0) {
                    win.draw(plus_fuel);
                }
                win.draw(text_earth);
                win.draw(text_newStar);
                win.draw(radar_line);
                win.draw(circle);

                win.display();
                if (circle.getPosition().x > 900) {
                    game_music.stop();
                    sound_vic.play();
                }
            }
            else {
                win.clear();

                win.draw(Space_rect2);
                win.draw(Space_rect);
                win.draw(Game_rect);
                
                
                win.draw(end_game);
                win.display();
                if (clock_text.getElapsedTime() > seconds(20)) win.close();
            }
        }
 else {
     win.draw(text_pause);
     win.display();
        }
    }

    return 0;
}


