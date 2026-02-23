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
