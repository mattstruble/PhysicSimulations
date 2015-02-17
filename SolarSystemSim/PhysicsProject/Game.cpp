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

	mp_SolarSystem = new SolarSystem();
	mp_SolarSystem->Initialize();

	GravityForceGenerator* gravity = new GravityForceGenerator(mp_PhysicObjectHandler);
	
	std::vector<Planet*> planets = mp_SolarSystem->GetPlanets();
	std::vector<PhysicObject*> po_Planets;

	for (unsigned int i = 0; i < planets.size(); i++)
	{
		po_Planets.push_back(planets[i]);
	}

	mp_PhysicObjectHandler->Add(po_Planets);
	mp_PhysicObjectHandler->AddToRegistry(po_Planets, gravity);
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
}
//================================================================================