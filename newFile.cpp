#include "src/headers/AdamLib.hpp"


void renderFloor(BasicNode* parent){}
void logicFloor(Component<BasicNode*>* host){}

//--------------------------------------------------

Scene* newScene()
{
	Scene* newScene = new Scene(0,0,1280,720);
	newScene->setCamera(0,0,1280,720);


//floor1
{
	BasicNode* floor1 = new BasicNode(newScene, renderFloor);
	floor1->setPos(0, 700);
	floor1->setDim(640, 20);
	floor1->setTexture("assets/box.png.png");
	floor1->addComponent("floor1", logicFloor);
	newScene->sceneNodes.push_back(floor1);

}
//floor2
{
	BasicNode* floor2 = new BasicNode(newScene, renderFloor);
	floor2->setPos(0, 360);
	floor2->setDim(20, 360);
	floor2->setTexture("assets/box.png.png");
	floor2->addComponent("floor2", logicFloor);
	newScene->sceneNodes.push_back(floor2);

}
//floor3
{
	BasicNode* floor3 = new BasicNode(newScene, renderFloor);
	floor3->setPos(620, 360);
	floor3->setDim(20, 360);
	floor3->setTexture("assets/box.png.png");
	floor3->addComponent("floor3", logicFloor);
	newScene->sceneNodes.push_back(floor3);

}
//floor4
{
	BasicNode* floor4 = new BasicNode(newScene, renderFloor);
	floor4->setPos(0, 360);
	floor4->setDim(640, 20);
	floor4->setTexture("assets/box.png.png");
	floor4->addComponent("floor4", logicFloor);
	newScene->sceneNodes.push_back(floor4);

}



	return newScene;
}