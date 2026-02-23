//
// Created by 101142429 on 2/21/2026.
//

#ifndef DUALIE_PLATFORMER_SCENE_H
#define DUALIE_PLATFORMER_SCENE_H
#include <Dualie/Graphics/RenderWindow.hpp>


class Scene {

protected:
	const float* m_dt;
public:
	explicit Scene (const float* dt);
	virtual ~Scene() = default;

	virtual void render(dl::RenderWindow& window) = 0;
	virtual void update() = 0;




};


#endif //DUALIE_PLATFORMER_SCENE_H