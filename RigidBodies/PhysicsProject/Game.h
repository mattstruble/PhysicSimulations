//======================================================================
//File: GameApp.h
//Author: Matt Struble
//======================================================================
#ifndef GAME_H
#define GAME_H
//======================================================================
#pragma once
//======================================================================
#include "Camera.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "HUD.h"
#include "PhysicObjectHandler.h"
#include "SolarSystem.h"
#include "GravityForceGenerator.h"
#include "BlobSystem.h"
#include "RigidBodySystem.h"
//======================================================================
class Game
{
public:
	Game();
	~Game();

	void Init(int width, int height);
	void Update(float gameTime);
	void Draw();
	void CleanUp();
	void HandleMouse(Vector2D mousePos);
	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);

private:
	Camera* mp_Camera;
	HUD* mp_HUD;
	PhysicObjectHandler* mp_PhysicObjectHandler;
	SolarSystem* mp_SolarSystem;
	BlobSystem* mp_BlobSystem;
	RigidBodySystem* mp_RigidBodySystem;

	int m_ScreenWidth;
	int m_ScreenHeight;
};
#endif