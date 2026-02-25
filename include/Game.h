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



    Scene *m_currentScene;

    void renderCurrentScene();

    void update();

public:
    static float DT;
    static dl::Clock GlobalClock;

    Game();
    ~Game();

    void run();

    static void handleEvents(dl::HOOK_TYPE type);
};


#endif //DUALIE_PLATFORMER_GAME_H
