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
#include "Tools.h"

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
    clickCount = 0;
    initUI();
    return true;
}

void GameScene::initUI()
{
    auto size = Director::getInstance()->getVisibleSize();
    
    auto node = NodeGrid::create();
    node->setTag(NODE);
    this->addChild(node);
    
    //Init background.
    auto bg = LayerColor::create(Color4B::BGREEN, size.width, size.height);
    node->addChild(bg);
    bg->setTag(BG);
    
    //Init ground.
    auto ground = LayerColor::create(Color4B::BYELLOW, size.width, 150);
    node->addChild(ground);
    ground->setTag(GROUND);
    
    //Init pause button.
//    auto pauseItem = MenuItemImage::create(
//                                           "pause.jpg",
//                                           "pause.jpg",
//                                           CC_CALLBACK_1(GameScene::menuPauseCallback, this));
//    
//	pauseItem->setPosition(Point(size.width - 50, size.height - 50));
//	auto pauseMenu = Menu::create(pauseItem, NULL);
//	pauseMenu->setPosition(Point::ZERO);
//    pauseMenu->setScale(0.5);
//	node->addChild(pauseMenu);
//    pauseMenu->setTag(PAUSE);
    
    //Init start button and tips.
    auto startItem = MenuItemImage::create(
                                           "start1.png",
                                           "start1.png",
                                           CC_CALLBACK_1(GameScene::menuStartCallback, this));
    
	startItem->setPosition(Point(size.width/2, size.height/2));
	auto startMenu = Menu::create(startItem, NULL);
	startMenu->setPosition(Point::ZERO);
    startMenu->setScale(0.4);
	node->addChild(startMenu);
    startMenu->setTag(START);
    
    LanguageType lan = Application::getInstance()->getCurrentLanguage();
    LabelTTF* tips;
    if (lan == LanguageType::CHINESE) {
        tips = LabelTTF::create("点击屏幕跳跃，可以连续跳跃两次", "Arial", 30);
    } else {
        tips = LabelTTF::create("Touch to jump, it can jump twice!", "Arial", 27);
    }
    tips->setColor(Color3B::BLACK);
    
    auto tipsSize = tips->cocos2d::Node::getContentSize();
    // position the label on the center of the screen
    tips->setPosition(Point((size.width - tipsSize.width)/2,60));
    node->addChild(tips);

    auto score = LabelTTF::create("SCORE : 0", "Arial", 30);
    score->setColor(Color3B::BLACK);
    auto scoreSize = tips->cocos2d::Node::getContentSize();
    // position the label on the center of the screen
    score->setPosition(Point((size.width - scoreSize.width)/2,size.height - 119));
    node->addChild(score);
    score->setTag(SCORE);
    
    box = LayerColor::create(Color4B::BBLUE, 50, 50);
    box->setPosition(Point(0, 150));
    node->addChild(box);
    box->setTag(PLAYER);
}

void GameScene::updateScore()
{
    auto node = this->getChildByTag(NODE);
    auto score = (LabelTTF*)(node->getChildByTag(SCORE));
    ostringstream oss;
    oss << "SCORE : " << (stageCount-1);
    score->setString(oss.str());
}

void GameScene::nextStage()
{
	stageCount++;
	ostringstream oss;
	oss << "stage_" << stageCount << ".xml";
	string stage = oss.str();
	drawStage(stage);
}

void GameScene::drawStage(const std::string &filename)
{
    auto node = this->getChildByTag(NODE);
    ItemFactory::getInstance()->createStage(*node, filename);
}

void GameScene::update(float f)
{
    auto size = Director::getInstance()->getVisibleSize();
    auto actionManager = Director::getInstance()->getActionManager();
    auto itemsVec = ItemFactory::getInstance()->itemArr;
    
    if (box->getPositionY() <= 151)
    {
        clickCount = 0;
    }
    
    for (auto item: itemsVec)
    {
        if(item->getBoundingBox().intersectsRect(box->getBoundingBox()))
        {
            auto node = this->getChildByTag(NODE);
            actionManager->removeAllActions();
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->removeAllEventListeners();
            unscheduleUpdate();
            
            int bScore = Tools::getInstance()->getBestScore();
            if (stageCount - 1 > bScore)
            {
                Tools::getInstance()->setBestScore(stageCount - 1);
                
                ostringstream oss;
                oss << "NEW BEST : " << (stageCount - 1);
                string best = oss.str();
                
                auto score = LabelTTF::create(best, "Arial", 30);
                score->setColor(Color3B::BLACK);
                auto scoreSize = score->cocos2d::Node::getContentSize();
                // position the label on the center of the screen
                score->setPosition(Point((size.width - scoreSize.width)/2,size.height - 169));
                node->addChild(score);
                score->setTag(BEST);
                
                auto c_score = (LabelTTF*)(node->getChildByTag(SCORE));
                c_score->setVisible(false);

            } else {
                ostringstream oss;
                oss << "BEST : " << bScore;
                string best = oss.str();
                
                auto score = LabelTTF::create(best, "Arial", 30);
                score->setColor(Color3B::BLACK);
                auto scoreSize = score->cocos2d::Node::getContentSize();
                // position the label on the center of the screen
                score->setPosition(Point((size.width - scoreSize.width)/2,size.height - 169));
                node->addChild(score);
                score->setTag(BEST);

            }
            
            auto startItem = MenuItemImage::create(
                                                   "restart1.png",
                                                   "restart1.png",
                                                   CC_CALLBACK_1(GameScene::menuStartCallback, this));
            
            startItem->setPosition(Point(size.width/2, size.height/2));
            auto startMenu = Menu::create(startItem, NULL);
            startMenu->setPosition(Point::ZERO);
            startMenu->setScale(0.4);
            node->addChild(startMenu);
			stageCount = 1;
            startMenu->setTag(START);
            return;
        }
    }
    
    if(box->getPositionX() >= size.width)
    {
        auto size = Director::getInstance()->getVisibleSize();
    
        actionManager->removeAllActions();
        
        nextStage();
        updateScore();
        box->setPosition(0, 150);
		box->runAction(MoveBy::create(speed_time, Point(size.width, 0)));

    }
}

void GameScene::onTouchesBegan(const vector<Touch*>& touches, Event* event)
{
    if(clickCount < 1)
    {
        clickCount++;
        auto action = JumpBy::create(0.5f, Point(0, 0), jump_height, 1);
        box->runAction(action);
    }
}

void GameScene::ACallback(Node* sender)
{
    
}

void GameScene::menuStartCallback(Ref* pSender)
{
    auto node = this->getChildByTag(NODE);
    clickCount = 0;
    stageCount = 1;
    updateScore();
    drawStage(temp);
    auto startMenu = node->getChildByTag(START);
    startMenu->removeFromParent();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto b_score = (LabelTTF*)(node->getChildByTag(BEST));
    if (b_score) b_score->removeFromParent();
    auto c_score = (LabelTTF*)(node->getChildByTag(SCORE));
    c_score->setVisible(true);
    
    auto size = Director::getInstance()->getVisibleSize();
    box->setPosition(0, 150);
	box->runAction(MoveBy::create(speed_time, Point(size.width, 0)));
    
    scheduleUpdate();
}

void GameScene::menuPauseCallback(Ref* pSender)
{
    Director::getInstance()->getActionManager()->pauseAllRunningActions();
}



