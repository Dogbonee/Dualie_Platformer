//
// Created by 101142429 on 2/21/2026.
//

#ifndef DUALIE_PLATFORMER_GAME_H
#define DUALIE_PLATFORMER_GAME_H
#include <Scene.h>
#include <Dualie/Graphics.hpp>
#include <Dualie/System/Clock.hpp>
#include <PlatformerScene.h>


class Game {
    const int TOP_WIDTH = 400;
    const int TOP_HEIGHT = 240;

    const int BOTTOM_WIDTH = 320;
    const int BOTTOM_HEIGHT = 240;

    dl::RenderWindow *m_window;
    dl::Clock m_globalClock;
    float m_dt;

    Scene *m_currentScene;

    void renderCurrentScene();

    void update();

public:
    Game();

    ~Game();

    void run();
};


#endif //DUALIE_PLATFORMER_GAME_H
