//
// Created by 101142429 on 2/23/2026.
//

#ifndef DUALIE_PLATFORMER_ENTITY_H
#define DUALIE_PLATFORMER_ENTITY_H

#include <Dualie/Graphics.hpp>
#include <Settings.h>
#include <algorithm>
#include <cmath>
#include <stdio.h>
typedef std::vector<std::vector<dl::Sprite *> > Level;


class Entity {

protected:
    dl::SpriteSheet *p_spriteSheet;
    Level *p_level;

    dl::Sprite m_sprite;
    dl::Vector2f m_velocity;
    dl::Vector2f m_attemptedVelocity;
    dl::Vector2f m_initialPosition;
    float m_maxSpeed;
    float m_acceleration;
    float m_friction;
    float m_gravity;
    float m_jumpForce;
    bool m_isOnGround;
    bool m_facingRight;

    float m_animationClock;
    float m_frameTime;
    bool m_animationRunning;

    int m_frames;
    int m_currentFrame;
    int m_sheetOffset;


public:
    Entity(dl::Vector2f initialPosition, dl::SpriteSheet& spriteSheet, Level *level);

    virtual ~Entity() = default;

    virtual int handleMovement(float dt);

    virtual void handleCollision(float dt);

    virtual bool handleAnimation(float dt);

    virtual void drawEntity(dl::RenderWindow &window);

    const dl::Vector2f& getPosition() const;
    dl::FloatRect getGlobalBounds() const;




};


#endif //DUALIE_PLATFORMER_ENTITY_H