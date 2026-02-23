//
// Created by 101142429 on 2/21/2026.
//

#include "../include/PlatformerScene.h"


PlatformerScene::PlatformerScene(const float *m_dt) : Scene(m_dt)
{
    dl::SpriteSheet *idleSpriteSheet = new dl::SpriteSheet();
    dl::SpriteSheet *runSpriteSheet = new dl::SpriteSheet();
    dl::SpriteSheet *jumpUpSpriteSheet = new dl::SpriteSheet();
    dl::SpriteSheet *jumpDownSpriteSheet = new dl::SpriteSheet();
    idleSpriteSheet->loadFromFile("romfs:/gfx/player_idle.t3x");
    runSpriteSheet->loadFromFile("romfs:/gfx/player_run.t3x");
    jumpUpSpriteSheet->loadFromFile("romfs:/gfx/player_jump_up.t3x");
    jumpDownSpriteSheet->loadFromFile("romfs:/gfx/player_jump_down.t3x");
    m_playerSpriteSheets.emplace_back(idleSpriteSheet);
    m_playerSpriteSheets.emplace_back(runSpriteSheet);
    m_playerSpriteSheets.emplace_back(jumpUpSpriteSheet);
    m_playerSpriteSheets.emplace_back(jumpDownSpriteSheet);

    m_tileSpriteSheet.loadFromFile("romfs:/gfx/tileset.t3x");
    m_player = new Player(m_playerSpriteSheets, &m_level);

    m_backgroundSpriteSheet.loadFromFile("romfs:/gfx/background.t3x");
    m_backgroundSprite.loadFromSpriteSheet(m_backgroundSpriteSheet, 0);
    m_backgroundSprite.setScale({2, 2});
    m_backgroundSprite.viewShouldAffect(false);


    loadLevel(0);
}

PlatformerScene::~PlatformerScene()
{
    delete m_player;

    for (auto &sheet: m_playerSpriteSheets)
    {
        delete sheet;
    }

    for (auto &row: m_level)
    {
        for (auto &tile: row)
        {
            if (tile)
            {
                delete tile;
            }
        }
    }
}


void PlatformerScene::loadLevel(int levelIndex)
{
    std::ifstream levelFile;
    levelFile.open("romfs:/levels/level1.lvl");
    std::string buf;

    for (int row = 0; std::getline(levelFile, buf); row++)
    {
        m_level.emplace_back();
        std::stringstream ss(buf);
        int tileBuf;
        for (int col = 0; ss >> tileBuf; col++)
        {
            if (tileBuf != 0)
            {
                dl::Sprite *tile = new dl::Sprite;
                tile->loadFromSpriteSheet(m_tileSpriteSheet, tileBuf - 1);
                tile->setPosition({static_cast<float>(col * TILE_SIZE), static_cast<float>(row * TILE_SIZE)});
                m_level.back().push_back(tile);
            } else
            {
                m_level.back().push_back(nullptr);
            }
        }
    }
    levelFile.close();
}


void PlatformerScene::render(dl::RenderWindow &window)
{
    window.clear(dl::TOP_SCREEN, dl::Color(128, 128, 128));
    window.draw(m_backgroundSprite);
    for (auto &row: m_level)
    {
        for (auto &tile: row)
        {
            if (tile)
            {
                window.draw(*tile);
            }
        }
    }
    m_player->drawPlayer(window); // Player will also display, so put all draw calls above this
}

void PlatformerScene::update()
{
    m_player->handleMovement(*m_dt);
    m_player->handleAnimation(*m_dt);
}
