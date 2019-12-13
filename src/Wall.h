#pragma once
#ifndef __Wall__
#define __Wall__

#include <vector>

#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"

class Wall :
	public DisplayObject
{
public:
	Wall();
	~Wall();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

	// pathfinding behaviours
	Tile* getTile();
	void setTile(Tile* newTile);

private:
	Tile* m_currentTile;
};


#endif /* defined (__Wall__) */