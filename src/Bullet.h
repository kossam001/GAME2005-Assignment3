#pragma once
#ifndef __Bullet__
#define __Bullet__

#include <vector>

#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"

class Bullet :
	public DisplayObject
{
public:
	Bullet();
	~Bullet();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

	// pathfinding behaviours
	Tile* getTile();
	void setTile(Tile* newTile);

private:
	Tile* m_currentTile;
	float m_angle;
	float m_speed;
};


#endif /* defined (__Bullet__) */#pragma once
