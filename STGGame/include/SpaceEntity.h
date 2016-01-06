//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "BaseApplication.h"
#include "MovableText.h"
#include "CSingleton.h"
#include "AudioManager.h"
#include "WorldManager.h"
#include <boost/pool/object_pool.hpp>

using namespace Ogre;



class SpaceText 
{
public:
	SceneNode *node;
	MovableText *msg;
	int tag;
	SpaceText()
	{

	}
	~SpaceText()
	{
		delete msg;
		node->getParentSceneNode()->removeAndDestroyChild(node->getName());
	}
};

class SpaceEntity
{
private:

public:
	SpaceEntity(void)
	{

	}
	virtual ~SpaceEntity(void)
	{
	}

	Real k;
	Real vx,vy;
	Real ax,ay;
	Real fx,fy;
	Real speedRate;

	bool isAlive;

	SceneNode *node;
	MovableObject *movableObject;

	Vector3 rotateAxis;

};

class CommonTool
{

public:

	static void DestroyAllAttachedMovableObjects( SceneNode* i_pSceneNode )
	{
		if ( !i_pSceneNode )
		{

			return;
		}

		// Destroy all the attached objects
		SceneNode::ObjectIterator itObject = i_pSceneNode->getAttachedObjectIterator();

		while ( itObject.hasMoreElements() )
		{
			MovableObject* pObject = static_cast<MovableObject*>(itObject.getNext());
			i_pSceneNode->getCreator()->destroyMovableObject( pObject );
		}

		// Recurse to child SceneNodes
		SceneNode::ChildNodeIterator itChild = i_pSceneNode->getChildIterator();

		while ( itChild.hasMoreElements() )
		{
			SceneNode* pChildNode = static_cast<SceneNode*>(itChild.getNext());
			DestroyAllAttachedMovableObjects( pChildNode );
		}
	}
};

class ObjectManager
{
public:
	

	virtual void Init()
	{
		sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		SetupContent();
	}

	virtual void SetupContent()
	{

	}
	virtual void InjectKeyDown(const OIS::KeyEvent& evt)
	{

	}
	virtual void InjectKeyUp(const OIS::KeyEvent& evt)
	{

	}
	virtual void InjectMouseMove( const OIS::MouseEvent& evt )
	{

	}
	virtual void InjectMouseDown( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
	{

	}
	virtual void InjectMouseUp( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
	{

	}

	void Reset()
	{

	}

	ObjectManager()
	{

	}
	virtual ~ObjectManager()
	{

	}
protected:
	SceneManager *sceneMgr;

};