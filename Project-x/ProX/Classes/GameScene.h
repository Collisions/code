//
//  GameScene.h
//  PX
//
//  Created by  YueBinbin on 14-5-31.
//
//  Game hud

#ifndef __PX__GameScene__
#define __PX__GameScene__

#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
    void menuPauseCallback(Ref* pSender);
    void menuStartCallback(Ref* pSender);
    
    void onTouchesBegan(const vector<Touch*>& touches, Event* event);
    
    void initUI();
    void updateScore();
    void nextStage();
    void drawStage(const string &filename);
    
    void update(float f);
    
    LayerColor* box;
    
    int stageCount;

<<<<<<< HEAD



	string temp = "stage_61.xml";


=======
	string temp = "stage_1.xml";
>>>>>>> 7202e0d1ea257d8f092ed44ec0261099cc25a3c8

    void ACallback(Node* sender);
    
    int clickCount;

	float speed_time = 2.3f;

	float jump_height = 90;
};

#endif /* defined(__PX__GameScene__) */
