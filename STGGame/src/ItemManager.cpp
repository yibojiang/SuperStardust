#include "ItemManager.h"


void ItemManager::SetupContent(Item& item)
{
	BillboardSet* bbs= sceneMgr->createBillboardSet(1);
	bbs->createBillboard(Vector3::ZERO,ColourValue(0,0,1));
	bbs->setMaterialName("Examples/Flare");
	bbs->setDefaultHeight(10);
	bbs->setDefaultWidth(10);

	SceneNode *node=sceneMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(bbs);
	node->setVisible(false);
	Entity *ent = sceneMgr->createEntity("bullet_boundingbox.mesh");
	node->attachObject(ent);
	item.node=node;
	item.movableObject=ent;	

}


void ItemManager::Init(SceneManager& sMgr)
{
	sceneMgr=&sMgr;

}

void ItemManager::AddTime(Real deltaTime)
{

}

void ItemManager::SetItem(ItemType itemType,Vector3 pos)
{
#pragma region 生成一个Item

	Item *item=new Item();
	SetupContent(*item);
	item->isAlive=true;
	item->node->setPosition(pos);
	item->itemType=itemType;
	itemList.push_back(item);

#pragma endregion

#pragma region 从数组中获得一个Item

#pragma endregion
}

ItemManager::ItemManager(void)
{
}


ItemManager::~ItemManager(void)
{
}