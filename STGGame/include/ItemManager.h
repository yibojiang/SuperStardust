//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include <list>
#include "Item.h"
#include "ToggleManager.h"


class ItemManager:public ObjectManager
{
private:
	boost::object_pool<Item> itemPool;
	void SetupContent()
	{
		BillboardSet* bbs;
		bbs= sceneMgr->createBillboardSet(1);
		bbs->createBillboard(Vector3::ZERO,ColourValue::White);
		bbs->setMaterialName("STGGame/Explosion01");
		bbs->setMaterialName("STGGame/Explosion02");
		bbs->setMaterialName("STGGame/Blast");

	}
	void SetupContent(Item& item,int size=16,Degree rotateDegree=Degree(0))
	{
		BillboardSet* bbs;

		
		switch (item.itemType)
		{
		case ItemType::UPGREADE_GREENBULLET:
			bbs= sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(0,1,0));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(10);
			bbs->setDefaultWidth(10);

			item.materialPtr=bbs->getMaterial()->clone(bbs->getName());
			bbs->setMaterialName(bbs->getName());

			item.node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			item.node->attachObject(bbs);
			item.movableObject = sceneMgr->createEntity("boundingbox_3.mesh");
			item.node->attachObject(item.movableObject);

			break;
		case ItemType::UPGREADE_BLUEBULLET:
			bbs= sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(0,0,1));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(10);
			bbs->setDefaultWidth(10);

			item.materialPtr=bbs->getMaterial()->clone(bbs->getName());
			bbs->setMaterialName(bbs->getName());

			item.node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			item.node->attachObject(bbs);
			item.movableObject = sceneMgr->createEntity("boundingbox_3.mesh");
			item.node->attachObject(item.movableObject);

			break;
		case ItemType::UPGREADE_REDBULLET:
			bbs= sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(1,0,0));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(10);
			bbs->setDefaultWidth(10);

			item.materialPtr=bbs->getMaterial()->clone(bbs->getName());
			bbs->setMaterialName(bbs->getName());


			item.node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			item.node->attachObject(bbs);
			item.movableObject = sceneMgr->createEntity("boundingbox_3.mesh");
			item.node->attachObject(item.movableObject);

			break;
		case ItemType::SCORE_1000:
			bbs= sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(1,1,1));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(10);
			bbs->setDefaultWidth(10);

			item.materialPtr=bbs->getMaterial()->clone(bbs->getName());
			bbs->setMaterialName(bbs->getName());


			item.node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			item.node->attachObject(bbs);
			item.movableObject = sceneMgr->createEntity("boundingbox_3.mesh");
			item.node->attachObject(item.movableObject);

			break;
		case ItemType::BOMB:
			bbs= sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(0.6,0.6,0));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(10);
			bbs->setDefaultWidth(10);

			item.materialPtr=bbs->getMaterial()->clone(bbs->getName());
			bbs->setMaterialName(bbs->getName());


			item.node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			item.node->attachObject(bbs);
			item.movableObject = sceneMgr->createEntity("boundingbox_3.mesh");
			item.node->attachObject(item.movableObject);

			break;
		case ItemType::EXTRA_SHIP:
			bbs= sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(0.8,0.6,1));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(10);
			bbs->setDefaultWidth(10);

			item.materialPtr=bbs->getMaterial()->clone(bbs->getName());
			bbs->setMaterialName(bbs->getName());


			item.node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			item.node->attachObject(bbs);
			item.movableObject = sceneMgr->createEntity("boundingbox_3.mesh");
			item.node->attachObject(item.movableObject);

			break;
		case ItemType::EXPLOSION_1:

			bbs= sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue::White);
			bbs->setMaterialName("STGGame/Explosion01");
			bbs->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureRotate(rotateDegree);
			
			item.materialPtr=bbs->getMaterial()->clone(bbs->getName());
			bbs->setMaterialName(bbs->getName());

			bbs->setDefaultHeight(size);
			bbs->setDefaultWidth(size);
			
			item.node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			item.node->attachObject(bbs);
			item.movableObject = sceneMgr->createEntity("bullet_boundingbox.mesh");
			item.node->attachObject(item.movableObject);


			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_EXPLOSION_WITH_BASS2,true);
			break;
		case ItemType::EXPLOSION_2:
			bbs= sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue::White);

			
			bbs->setMaterialName("STGGame/Explosion02");
			bbs->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureRotate(rotateDegree);
			
			item.materialPtr=bbs->getMaterial()->clone(bbs->getName());
			bbs->setMaterialName(bbs->getName());

			bbs->setDefaultHeight(size);
			bbs->setDefaultWidth(size);
			item.node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			item.node->attachObject(bbs);
			item.movableObject = sceneMgr->createEntity("bullet_boundingbox.mesh");
			item.node->attachObject(item.movableObject);

			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_EXPLOSION_WITH_BASS2,true);
			break;
		case ItemType::EXPLOSION_3:
			break;

		case ItemType::EXPLOSION_FIRWORK_1:
			
			item.node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			item.ps=sceneMgr->createParticleSystem("firework"+item.node->getName(),"STGGame/FireworkExplosion");
			item.movableObject = sceneMgr->createEntity("bullet_boundingbox.mesh");
			item.node->attachObject(item.movableObject);
			item.node->attachObject(item.ps);
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_EXPLOSION_WITH_BASS2,true);
			break;
		default:
			break;
		}
		
	}
public:

	SINGLETON(ItemManager);


	//遍历的物品
	std::list<Item*> itemList;


	void AddTime(Real deltaTime)
	{
		for (std::list<Item*>::iterator it = itemList.begin(); it != itemList.end();)
		{
			if ((*it)->isAlive)
			{
				if ( (*it)->hasTicker)
					if ((*it)->ticker->timeTicker<0)
					{
						//(*it)->ticker->isAlive=false;
						(*it)->isAlive=false;
					}
						
				it++;
			}
			else
			{
				itemPool.destroy(*it);
				//delete *it;
				it=itemList.erase(it);
			}
		}
	}

	Item& GenerateItem(SceneNode *node,int itemType,Degree degree,Degree distanceDegree)
	{
		Item *newItem;

		Vector3 dir=Vector3(0,-1,0);
		Real x,y;
		x=0;
		y=-1;

		dir.x=x*cos(degree.valueRadians())-y*sin(degree.valueRadians());
		dir.y=x*sin(degree.valueRadians())+y*cos(degree.valueRadians());

		newItem=&this->AddItem(itemType,Vector3(0,0,0));
		newItem->rotateAxis=node->convertLocalToWorldPosition(dir).crossProduct(node->getPosition()).normalisedCopy();
		newItem->node->rotate(newItem->rotateAxis,Degree(distanceDegree),Node::TS_LOCAL);
		newItem->node->translate(node->getPosition(),Node::TS_LOCAL);	
		return *newItem;
	}

	Item& AddItem(int itemType,Vector3 pos,int size=16,Degree rotateDegree=Degree(0))
	{
		Item *item= itemPool.construct();
		//Item *item=new Item();

		item->itemType=itemType;
		SetupContent(*item,size,rotateDegree);
		item->isAlive=true;
		item->node->setPosition(pos);
		item->node->setVisible(true);
		item->movableObject->setVisible(false);
		item->hasTicker=false;
		itemList.push_back(item);

		return *item;

	}

	Item& AddFirework(int itemType,Vector3 pos)
	{
		Item *newItem=&this->AddItem(itemType,pos);
		Toggle *newToggle=&INSTANCE(ToogleManager)->AddToggle(newItem->ps->getEmitter(0)->getTimeToLive());
		this->SetTicker(*newItem,*newToggle);
		newToggle->isActivated=true;
		return *newItem;
	}

	Item& AddExplosion(int itemType,Vector3 pos,int size=16,Degree rotateDegree=Degree(0))
	{
		Item *newItem=&this->AddItem(itemType,pos,size,rotateDegree);
		Toggle *newToggle=&INSTANCE(ToogleManager)->AddToggle(0.9);
		this->SetTicker(*newItem,*newToggle);
		newToggle->isActivated=true;
		return *newItem;
	}

	void AddRandomExplosion(Vector3 pos,int size=16)
	{
		int degree=Math::RangeRandom(0,360);
		int num=Math::RangeRandom(0,2);
		switch(num)
		{
		case 0:
			AddExplosion(ItemType::EXPLOSION_1,pos,size,Degree(degree));
			break;
		case 1:
			AddExplosion(ItemType::EXPLOSION_2,pos,size,Degree(degree));
			break;
		default:
			break;
		}
	}

	void Reset()
	{
		for (std::list<Item*>::iterator it = itemList.begin(); it != itemList.end();)
		{
			itemPool.destroy(*it);
			it=itemList.erase(it);
		}

	}

	void SetTicker(Item &item,Toggle& ticker)
	{
		item.hasTicker=true;
		item.ticker=&ticker;
	}

	ItemManager(void)
	{

	}

	~ItemManager(void)
	{

	}


};

