//
//  GameScene.cpp
//  PX
//
//  Created by  YueBinbin on 14-5-31.
//
//

#include "GameScene.h"
#include "resource.h"
#include "pugixml.hpp"
#include "ItemFactory.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
	auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
    
}

bool GameScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    stageCount = 1;
    
    initUI();
    //initStage();
    return true;
}

void GameScene::initUI()
{
    
    auto size = Director::getInstance()->getVisibleSize();
    
    //Init background.
    auto bg = LayerColor::create(Color4B::WHITE, size.width, size.height);
    this->addChild(bg);
    bg->setTag(BG);
    
    //Init ground.
    auto ground = LayerColor::create(Color4B::BLACK, size.width, 150);
    this->addChild(ground);
    ground->setTag(GROUND);
    
    //Init logo.
    auto logo = Sprite::create("CloseNormal.png");
    logo->setPosition(Point(size.width/2, size.height/3*2));
    logo->setTag(LOGO);
    this->addChild(logo);
    
    //Init pause button.
    auto pauseItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseNormal.png",
                                           CC_CALLBACK_1(GameScene::menuPauseCallback, this));
    
	pauseItem->setPosition(Point(size.width - 50, size.height - 50));
	auto pauseMenu = Menu::create(pauseItem, NULL);
	pauseMenu->setPosition(Point::ZERO);
	this->addChild(pauseMenu);
    pauseMenu->setTag(PAUSE);
    
    //Init start button and tips.
    auto startItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseNormal.png",
                                           CC_CALLBACK_1(GameScene::menuStartCallback, this));
    
	startItem->setPosition(Point(size.width/2, size.height/2));
	auto startMenu = Menu::create(startItem, NULL);
	startMenu->setPosition(Point::ZERO);
	this->addChild(startMenu);
    startMenu->setTag(START);
    
    box = LayerColor::create(Color4B::RED, 50, 50);
    box->setPosition(Point(0, 150));
    this->addChild(box);
    box->setTag(PLAYER);
}

void GameScene::initStage()
{
    drawStage("stage_1.xml");
}

void GameScene::nextStage()
{
    drawStage("stage_2.xml");
}

void GameScene::drawStage(const std::string &filename)
{
     ItemFactory::getInstance()->createStage(*this, filename);
}

void GameScene::update(float f)
{
    auto size = Director::getInstance()->getVisibleSize();
    auto actionManager = Director::getInstance()->getActionManager();
    auto itemsVec = ItemFactory::getInstance()->itemArr;
    
    for (auto item: itemsVec)
    {
        if(item->getBoundingBox().intersectsRect(box->getBoundingBox()))
        {
            actionManager->removeAllActions();
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->removeAllEventListeners();
            unscheduleUpdate();
            
            auto startItem = MenuItemImage::create(
                                                   "CloseNormal.png",
                                                   "CloseNormal.png",
                                                   CC_CALLBACK_1(GameScene::menuStartCallback, this));
            
            startItem->setPosition(Point(size.width/2, size.height/2));
            auto startMenu = Menu::create(startItem, NULL);
            startMenu->setPosition(Point::ZERO);
            this->addChild(startMenu);
            startMenu->setTag(START);
            return;
        }
    }
    
    if(box->getPositionX() >= size.width)
    {
        auto size = Director::getInstance()->getVisibleSize();
    
        actionManager->removeAllActions();
        
        nextStage();

        box->setPosition(0, 150);
        box->runAction(MoveBy::create(2, Point(size.width, 0)));

    }
}

void GameScene::onTouchesBegan(const vector<Touch*>& touches, Event* event)
{
    auto actionBy = JumpBy::create(0.5f, Point(0, 0), 80, 1);
    box->runAction(actionBy);
}

void GameScene::menuStartCallback(Ref* pSender)
{
    drawStage("stage_1.xml");
    auto logo = getChildByTag(LOGO);
    if(logo)logo->removeFromParent();
    auto startMenu = getChildByTag(START);
    startMenu->removeFromParent();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto size = Director::getInstance()->getVisibleSize();
    box->setPosition(0, 150);
    box->runAction(MoveBy::create(2, Point(size.width, 0)));
    
    scheduleUpdate();
}

void GameScene::menuPauseCallback(Ref* pSender)
{
    //Director::getInstance()->pause();
}



