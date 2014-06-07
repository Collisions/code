//
//  ItemFactory.h
//  ProX
//
//  Created by  YueBinbin on 14-6-4.
//
//

#ifndef __ProX__ItemFactory__
#define __ProX__ItemFactory__

#include "cocos2d.h"

using namespace cocos2d;

class ItemFactory
{
public:
    static ItemFactory* getInstance();
    
    Vector<Node*> itemArr;
    
    void init();
    
    void createStage(Node &parent, const std::string &filename);
    
    Color3B getColor(int color);
    
    int str2num(const std::string &str);
    
    void setPositionByStr(Node &node, const std::string &pos);
    
    void createAction(Node &node, int type, int dura, const std::string &para);
};


#endif /* defined(__ProX__ItemFactory__) */
