//
// Created by 101142429 on 2/21/2026.
//

#ifndef DUALIE_PLATFORMER_PLAYER_H
#define DUALIE_PLATFORMER_PLAYER_H
#include <Dualie/Graphics.hpp>

typedef std::vector<std::vector<dl::Sprite *> > Level;

class Player {
    std::vector<dl::SpriteSheet *> *p_spriteSheets;
    dl::SpriteSheet **p_currentSheet;
    Level *p_level;

    dl::Sprite m_sprite;
    dl::Vector2f m_velocity;
    float m_speed;
    float m_gravity;
    float m_jumpForce;
    bool m_isOnGround;
    bool m_facingRight;

    float m_animationClock;
    float m_frameTime;

    int m_frames;
    int m_currentFrame;


    dl::View m_camera;
    float m_cameraSpeed;

public:
    Player(std::vector<dl::SpriteSheet *> &spriteSheet, Level *level);

    virtual ~Player() = default;

    void handleMovement(float dt);

    void handleAnimation(float dt);

    void drawPlayer(dl::RenderWindow &window);
};


#endif //DUALIE_PLATFORMER_PLAYER_H
