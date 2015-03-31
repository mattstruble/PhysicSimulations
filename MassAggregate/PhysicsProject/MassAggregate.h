//======================================================================
//File: MassAggregate.h
//Author: Matt Struble
//======================================================================
#ifndef MASS_AGGREGATE_H
#define MASS_AGGREGATE_H
//======================================================================
#pragma once
//======================================================================
#include "GameObject.h"
#include "ContactGenerator.h"
//======================================================================
class MassAggregate
{
public:
	MassAggregate() {};
	~MassAggregate() {};

	void Initialize(Vector3D position, float mass = 1);
	void Update(float dt);
	void Draw();
	void Clear();
	void Reset();

	inline std::vector<GameObject*> GetGameObjects() { return mp_GameObjects; };
	inline std::vector<ContactGenerator*> GetContactGenerators() { return mp_ContactGenerators; };

protected:
	void createRodContact(GameObject* one, GameObject* two);
	void createCableContact(GameObject* one, GameObject* two);

	std::vector<GameObject*> mp_GameObjects;
	std::vector<ContactGenerator*> mp_ContactGenerators;
};
#endif