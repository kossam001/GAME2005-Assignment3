#pragma once
#ifndef __Brick__
#define __Brick__

#include <vector>

#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"

class Brick :
	public DisplayObject
{
public:
	Brick();
	~Brick();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

	// pathfinding behaviours
	Tile* getTile();
	void setTile(Tile* newTile);

	float getAngle();
	float getSpeed();

private:
	Tile* m_currentTile;
	float m_angle;
	float m_speed;
	glm::vec2 m_lastLocation;
};


#endif /* defined (__Brick__) */#pragma once
