//
// Created by 101142429 on 2/21/2026.
//

#ifndef DUALIE_PLATFORMER_PLATFORMERSCENE_H
#define DUALIE_PLATFORMER_PLATFORMERSCENE_H
#include <Player.h>
#include <Scene.h>
#include <vector>
#include <fstream>
#include <sstream>


class PlatformerScene : public Scene {
    static constexpr int TILE_SIZE = 16;

    dl::SpriteSheet m_tileSpriteSheet;
    dl::SpriteSheet m_backgroundSpriteSheet;
    dl::Sprite m_backgroundSprite;

    std::vector<dl::SpriteSheet *> m_playerSpriteSheets;

    Player *m_player;

    Level m_level;

    void loadLevel(int levelIndex);

public:
    PlatformerScene(const float *m_dt);

    ~PlatformerScene() override;

    void render(dl::RenderWindow &window) override;

    void update() override;
};


#endif //DUALIE_PLATFORMER_PLATFORMERSCENE_H
