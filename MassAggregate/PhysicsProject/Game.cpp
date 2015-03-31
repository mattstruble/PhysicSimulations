//======================================================================
//File: Main.cpp
//Author: Matt Struble
//======================================================================
#include "Game.h"
//======================================================================
Game::Game()
{
	mp_Camera = nullptr;
	mp_HUD = nullptr;
	mp_PhysicObjectHandler = nullptr;
	mp_SolarSystem = nullptr;
	mp_BlobSystem = nullptr;
}

//--------------------------------------------------------------------------------
Game::~Game()
{

}

//--------------------------------------------------------------------------------
void Game::Init(int width, int height)
{
	m_ScreenWidth = width;
	m_ScreenHeight = height;

	mp_Camera = new Camera(width, height);
	mp_HUD = new HUD;
	mp_HUD->Init(10, 20);

	mp_PhysicObjectHandler = new PhysicObjectHandler();
	mp_PhysicObjectHandler->Initialize();

	//mp_SolarSystem = new SolarSystem();
	//mp_SolarSystem->Initialize(mp_PhysicObjectHandler);

	mp_BlobSystem = new BlobSystem();
	mp_BlobSystem->Initialize(mp_PhysicObjectHandler);
}

//--------------------------------------------------------------------------------
void Game::Update(float gameTime)
{
	mp_PhysicObjectHandler->Update(gameTime);

	mp_Camera->Update(); 
	
	mp_HUD->Update(gameTime);
}

void Game::Draw()
{
	mp_PhysicObjectHandler->Draw();
	mp_HUD->Draw();
}

//--------------------------------------------------------------------------------
void Game::HandleMouse(Vector2D mousePos)
{
	mp_Camera->HandleMouse(mousePos);
}

//--------------------------------------------------------------------------------
void Game::HandleMousePassive(int x, int y)
{
	mp_Camera->HandleMousePassive(x, y);
}

//--------------------------------------------------------------------------------
void Game::HandleKey(unsigned char key)
{
	mp_Camera->HandleKey(key);
	mp_HUD->HandleKey(key);
	mp_PhysicObjectHandler->HandleKey(key);

	if (isdigit(key))
	{
		mp_Camera->SetTarget(mp_PhysicObjectHandler->GetTarget());
		mp_HUD->SetTarget(mp_PhysicObjectHandler->GetTarget());
	}
}

//--------------------------------------------------------------------------------
void Game::CleanUp()
{
	delete mp_Camera;
	mp_Camera = nullptr;

	delete mp_HUD;
	mp_HUD = nullptr;

	delete mp_PhysicObjectHandler;
	mp_PhysicObjectHandler = nullptr;

	delete mp_SolarSystem;
	mp_SolarSystem = nullptr;

	delete mp_BlobSystem;
	mp_BlobSystem = nullptr;
}
//================================================================================