//
// Created by 101142429 on 2/21/2026.
//

#ifndef DUALIE_PLATFORMER_PLATFORMERSCENE_H
#define DUALIE_PLATFORMER_PLATFORMERSCENE_H
#include <Goblin.h>
#include <Player.h>
#include <Door.h>
#include <Scene.h>
#include <Heart.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <Dualie/>



class PlatformerScene : public Scene {


    dl::SpriteSheet m_tileSpriteSheet;
    dl::SpriteSheet m_backgroundSpriteSheet;
    dl::Sprite m_backgroundSprite;

    dl::SpriteSheet* m_playerSpriteSheet;
    dl::SpriteSheet* m_goblinSpriteSheet;
    dl::SpriteSheet* m_heartSpriteSheet;
    dl::SpriteSheet* m_doorSpriteSheet;

    Player *m_player;
    std::vector<Entity *> m_entities;
    std::vector<Heart> m_hearts;
    int m_expectedHealth;

    dl::Music

    Level m_level;

    void loadLevel(int levelIndex);

public:
    PlatformerScene(const float *m_dt);

    ~PlatformerScene() override;

    void render(dl::RenderWindow &window) override;

    void update() override;
};


#endif //DUALIE_PLATFORMER_PLATFORMERSCENE_H
