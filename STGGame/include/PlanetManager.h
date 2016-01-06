#pragma once
#include "Planet.h"

class PlanetType
{
public:
	enum PlanetId{
		Earth=0,
		Commet=1,
		Jupitar=2,
		Earth2,
	};
};


class PlanetManager:public ObjectManager
{
private:

	Light *light;
	ParticleSystem *ps;
	void SetupContent()
	{
		
	}
public:
	SINGLETON(PlanetManager);

	Planet *planet;
	void Init()
	{
		sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		planet=new Planet(90.1);
		
	}

	void SetRadius(float radius)
	{
		planet->radius=radius;

	}

	void SetType(int planetType)
	{
		ps=sceneMgr->createParticleSystem("Star","STGGame/Star");
		sceneMgr->getRootSceneNode()->attachObject(ps);

		planet->node = sceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(0,0,0));
		Entity *ent;
		switch(planetType)
		{
		case PlanetType::Earth:
			SetRadius(90.1);
			sceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
			ent = sceneMgr->createEntity("earth.mesh");
			planet->node->attachObject(ent);

			light = sceneMgr->createLight("DirectionLight");
			//light->setType(Ogre::Light::LT_POINT);
			//light->setType(Ogre::Light::LT_DIRECTIONAL);

			//light->setType(Ogre::Light::LT_SPOTLIGHT);
			//light->setPosition(Ogre::Vector3(300, 200, 300));
			light->setType(Ogre::Light::LT_DIRECTIONAL);
			light->setDirection(-1,-1,-1);
			

			
			//light->setSpotlightRange(Radian(Math::HALF_PI),Radian(Math::PI),1.0);
			light->setDiffuseColour(Ogre::ColourValue(1.0,0.8,0.8,1.0));
			light->setSpecularColour(Ogre::ColourValue(1.0,1.0,1.0,1.0));
			

			sceneMgr->setSkyBox(true, "STGGame/StarBox");
			break;
		case PlanetType::Commet:
			SetRadius(90.1);
			sceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
			ent = sceneMgr->createEntity("commet.mesh");
			planet->node->attachObject(ent);

			light = sceneMgr->createLight("PointLight");
			light->setType(Ogre::Light::LT_DIRECTIONAL);
			light->setPosition(Ogre::Vector3(300, 200, 300));
			light->setDirection(0,0,0);
			light->setDiffuseColour(Ogre::ColourValue::White);
			light->setSpecularColour(Ogre::ColourValue::White);

			sceneMgr->setSkyBox(true, "STGGame/StarBox");
			break;
		case PlanetType::Jupitar:
			SetRadius(90.1);
			sceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
			ent = sceneMgr->createEntity("Jupitar.mesh");
			planet->node->attachObject(ent);

			light = sceneMgr->createLight("DirectionLight");

			light->setType(Ogre::Light::LT_DIRECTIONAL);
			light->setDirection(-1,-1,-1);


			light->setDiffuseColour(Ogre::ColourValue(1.0,0.8,0.8,1.0));
			light->setSpecularColour(Ogre::ColourValue(1.0,1.0,1.0,1.0));


			sceneMgr->setSkyBox(true, "STGGame/StarBox");

			break;
		case PlanetType::Earth2:
			SetRadius(90.1);
			sceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
			ent = sceneMgr->createEntity("earth2.mesh");
			planet->node->attachObject(ent);

			light = sceneMgr->createLight("DirectionLight");

			light->setType(Ogre::Light::LT_DIRECTIONAL);
			light->setDirection(-1,-1,-1);


			light->setDiffuseColour(Ogre::ColourValue(1.0,0.8,0.8,1.0));
			light->setSpecularColour(Ogre::ColourValue(1.0,1.0,1.0,1.0));


			sceneMgr->setSkyBox(true, "STGGame/StarBox");

			break;
		default:
			break;
		}

	}


	
	void AddTime(Real deltaTime)
	{

	}

	void Reset()
	{
		sceneMgr->destroyLight(light);
		sceneMgr->destroyParticleSystem(ps);
		
		delete planet;
	}

	PlanetManager(void)
	{

	}
	~PlanetManager(void)
	{
		
	}
};

