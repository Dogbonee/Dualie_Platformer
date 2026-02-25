//
// Created by 101142429 on 2/21/2026.
//

#include "../include/PlatformerScene.h"




PlatformerScene::PlatformerScene(const float *m_dt) : Scene(m_dt), m_expectedHealth(MAX_HEALTH)
{
    m_playerSpriteSheet = new dl::SpriteSheet;
    m_goblinSpriteSheet = new dl::SpriteSheet;
    m_heartSpriteSheet = new dl::SpriteSheet;
    m_doorSpriteSheet = new dl::SpriteSheet;
    m_playerSpriteSheet->loadFromFile("romfs:/gfx/player_sheet.t3x");
    m_goblinSpriteSheet->loadFromFile("romfs:/gfx/goblin_sheet.t3x");
    m_heartSpriteSheet->loadFromFile("romfs:/gfx/heart.t3x");
    m_doorSpriteSheet->loadFromFile("romfs:/gfx/door.t3x");


    m_tileSpriteSheet.loadFromFile("romfs:/gfx/tileset.t3x");
    m_player = new Player({120, 120}, *m_playerSpriteSheet, &m_level);

    m_backgroundSpriteSheet.loadFromFile("romfs:/gfx/background.t3x");
    m_backgroundSprite.loadFromSpriteSheet(m_backgroundSpriteSheet, 0);
    m_backgroundSprite.setScale({2, 2});
    m_backgroundSprite.viewShouldAffect(false);


    for (int i = 0; i < 3; i++)
    {
        Heart heart({i * 90.f + 65.f, dl::RenderWindow::BOTTOM_HEIGHT / 2}, *m_heartSpriteSheet);
        m_hearts.push_back(heart);
    }

    loadLevel(1);
}

PlatformerScene::~PlatformerScene()
{
    delete m_player;

    for (auto &entity: m_entities)
    {
        delete entity;
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
    delete m_playerSpriteSheet;
    delete m_goblinSpriteSheet;
    delete m_heartSpriteSheet;
    delete m_doorSpriteSheet;
}


void PlatformerScene::loadLevel(int levelIndex)
{
    std::ifstream levelFile;
    char filePath[128];
    sprintf(filePath, "romfs:/levels/level%d.lvl", levelIndex);
    levelFile.open(filePath);
    std::string buf;

    for (int row = 0; std::getline(levelFile, buf); row++)
    {
        m_level.emplace_back();
        std::stringstream ss(buf);
        int tileBuf;
        for (int col = 0; ss >> tileBuf; col++)
        {
            if (tileBuf == -1)
            {
                Goblin *goblin = new Goblin({(col * TILE_SIZE * SPRITE_SCALE), (row * TILE_SIZE * SPRITE_SCALE)},
                                            *m_goblinSpriteSheet, &m_level, m_player);
                m_entities.push_back(goblin);
            } else if (tileBuf == -2)
            {
                Door* door = new Door({(col * TILE_SIZE * SPRITE_SCALE), (row * TILE_SIZE * SPRITE_SCALE)},
                                            *m_doorSpriteSheet, &m_level, m_player);
                m_entities.push_back(door);
            }
            if (tileBuf > 0)
            {
                dl::Sprite *tile = new dl::Sprite;
                tile->loadFromSpriteSheet(m_tileSpriteSheet, tileBuf - 1);
                tile->setScale({SPRITE_SCALE, SPRITE_SCALE});
                tile->setPosition({
                    static_cast<float>(col * TILE_SIZE * SPRITE_SCALE),
                    static_cast<float>(row * TILE_SIZE * SPRITE_SCALE)
                });
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
    for (auto &entity: m_entities)
    {
        entity->drawEntity(window);
    }
    m_player->drawEntity(window); // Player will also display, so put all draw calls above this

    window.clear(dl::BOTTOM_SCREEN);
    window.draw(m_backgroundSprite);
    for (auto &heart: m_hearts)
    {
        heart.drawHeart(window);
    }
    window.display();
}

void PlatformerScene::update()
{
    int playerHealth = m_player->handleMovement(*m_dt);
    m_player->handleAnimation(*m_dt);
    for (auto &entity: m_entities)
    {
        entity->handleMovement(*m_dt);
        entity->handleAnimation(*m_dt);
    }

    if (playerHealth != m_expectedHealth)
    {
        if (playerHealth == MAX_HEALTH)
        {
            for (auto &heart: m_hearts)
            {
                heart.restore();
            }
        }
        else if (playerHealth >= 0)
        {
            m_hearts[playerHealth].kill();
            m_expectedHealth = playerHealth;
        }
    }
}
