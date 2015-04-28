//======================================================================
//File: BlobSystem.cpp
//Author: Matt Struble
//======================================================================
#include "BlobSystem.h"
#include "ConstantGravityForceGenerator.h"
#include "CubeMA.h"
#include "TetrahedronMA.h"
#include "PyramidMA.h"
#include "GroundContact.h"
#include "GameObject.h"
#include "BlobGameParser.h"
//======================================================================
BlobSystem::BlobSystem()
{

}

BlobSystem::~BlobSystem()
{

}

void BlobSystem::Initialize(PhysicObjectHandler* handler)
{
	BlobGameParser parser;

	if (parser.Parse("../data/BlobGame.xml"))
	{
		ConstantGravityForceGenerator* gravity = parser.GetGravity();

		handler->Add(parser.GetGround());

		handler->AddContactGenerator(new GroundContact(0));

		std::vector<MassAggregate*> massObjects = parser.GetMassAggregates();
		std::vector<MassAggregate*>::iterator massIter;

		std::vector<GameObject*> gameObjects;
		std::vector<GameObject*>::iterator gameIter;

		for (massIter = massObjects.begin(); massIter != massObjects.end(); massIter++)
		{
			gameObjects = (*massIter)->GetGameObjects();

			for (gameIter = gameObjects.begin(); gameIter != gameObjects.end(); gameIter++)
			{
				handler->AddCollisionObject(static_cast<PhysicObject*>(*gameIter));
				handler->AddToRegistry((*gameIter), gravity);
			}

			handler->AddContactGenerator((*massIter)->GetContactGenerators());
		}
	}
	else
	{
		Debug::LOG(Color::AZURE, "Error parsing BlobGame.xml");
	}
}