//
// Created by 101142429 on 2/21/2026.
//

#include "Game.h"


Game::Game()
{
    m_window = new dl::RenderWindow();
    m_currentScene = new PlatformerScene(&m_dt);
}

Game::~Game()
{
    delete m_window;
    delete m_currentScene;
}

void Game::update()
{
    m_dt = m_globalClock.restart().asSeconds();
    m_currentScene->update();
    m_currentScene->render(*m_window);
}

void Game::run()
{
    m_window->InitPrintScreen(dl::BOTTOM_SCREEN);
    while (m_window->isOpen())
    {
        update();
    }
}
