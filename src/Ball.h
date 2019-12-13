#pragma once
#ifndef __Ball__
#define __Ball__

#include <vector>

#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"

class Ball :
	public DisplayObject
{
public:
	Ball();
	~Ball();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

	// pathfinding behaviours
	Tile* getTile();
	void setTile(Tile* newTile);

	void setAngle(float angle);
	void setSpeed(float speed);

	float getAngle();
	float getSpeed();

	void setVerticalDirection(int direction);
	void setHorizontalDirection(int direction);

	int getVerticalDirection();
	int getHorizontalDirection();

private:
	Tile* m_currentTile;
	float m_angle;
	float m_speed;

	int verticalDirection = 1;
	int horizontalDirection = 1;
};


#endif /* defined (__Ball__) */#pragma once
