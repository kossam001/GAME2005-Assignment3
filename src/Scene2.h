#pragma once
#ifndef __SCENE2__
#define __SCENE2__

#include "Scene.h"
#include "Label.h"
#include "ship.h"
#include "Bullet.h"
#include "MoveState.h"

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	/*Label* m_pStartLabel;
	Label* m_pInstructionsLabel;*/

	Ship* m_pShip;

	MoveState m_moveState;
	glm::vec2 m_speedFactor;

	glm::vec2 m_mousePosition;

	// ImGui utility functions
	void m_ImGuiKeyMap();
	void m_ImGuiSetStyle();
	void m_updateUI();

	// ImGui menu variables
	bool m_exitApp = false;
	bool m_displayAbout = false;
	bool m_displayUI = true;

	// Physics Variables
	float m_gravity = 9.8f;
	int m_PPM = 10; // pixels per meter
	glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
	glm::vec2 m_velocity = glm::vec2(0.0f, 0.0f);
	glm::vec2 m_acceleration = glm::vec2(0.0f, 0.0f);

	// Physics functions
	void m_move();

	Bullet* m_pBullets[10];
};

#endif /* defined (__SCENE2__) */