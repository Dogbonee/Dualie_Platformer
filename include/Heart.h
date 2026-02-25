//
// Created by 101142429 on 2/23/2026.
//

#ifndef DUALIE_PLATFORMER_HEART_H
#define DUALIE_PLATFORMER_HEART_H
#include <Dualie/Graphics.hpp>


class Heart {


    bool m_alive;
    dl::SpriteSheet* p_spriteSheet;
    dl::Sprite m_sprite;

public:
    Heart(dl::Vector2f initialPosition, dl::SpriteSheet& spriteSheet);
    void restore();
    void kill();
    void drawHeart(dl::RenderWindow &window);

};


#endif //DUALIE_PLATFORMER_HEART_H