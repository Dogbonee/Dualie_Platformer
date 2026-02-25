//
// Created by 101142429 on 2/21/2026.
//

#include "Game.h"

float Game::DT = 0.0f;
dl::Clock Game::GlobalClock;

Game::Game()
{
    m_window = new dl::RenderWindow();
    m_currentScene = new PlatformerScene(&DT);
    m_window->registerHookCallback(handleEvents);
}

Game::~Game()
{
    delete m_window;
    delete m_currentScene;
}

void Game::update()
{
    DT = GlobalClock.restart().asSeconds();
    m_currentScene->update();
    m_currentScene->render(*m_window);
}

void Game::run()
{
    while (m_window->isOpen())
    {
        update();
    }
}

void Game::handleEvents(dl::HOOK_TYPE type)
{
    if (type == dl::HOOK_TYPE::RESTORE || type == dl::HOOK_TYPE::WAKEUP)
    {
        DT = GlobalClock.restart().asSeconds();
    }
}
