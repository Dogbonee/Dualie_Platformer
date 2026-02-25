//
// Created by 101142429 on 2/21/2026.
//

#ifndef DUALIE_PLATFORMER_PLAYER_H
#define DUALIE_PLATFORMER_PLAYER_H
#include <Dualie/Graphics.hpp>
#include <Settings.h>
#include <Entity.h>
#include <algorithm>


class Player : public Entity {
    dl::View m_camera;

    bool m_hit;
    bool m_dead;
    bool m_invincible;
    int m_lives;
    int m_health;


    float m_invincibleTimer;
    float m_invincibleTime;

    float m_deathTimer;
    float m_deathTime;

public:
    Player(const dl::Vector2f &initialPosition, dl::SpriteSheet &spriteSheet, Level *level);

    virtual ~Player() = default;

    int handleMovement(float dt) override;

    bool handleAnimation(float dt) override;

    void hit(bool fromRight);

    void drawEntity(dl::RenderWindow &window) override;

    const bool& isDead() const;
};


#endif //DUALIE_PLATFORMER_PLAYER_H
