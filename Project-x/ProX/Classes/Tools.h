//
//  Tools.h
//  ProX
//
//  Created by  YueBinbin on 14-6-17.
//
//

#ifndef __ProX__Tools__
#define __ProX__Tools__

#include "cocos2d.h"
USING_NS_CC;

class Tools
{
public:
    static Tools* getInstance();
    
    std::vector<std::string> splitStr(const std::string &str, const std::string &ch);
    
    int getBestScore();
    
    void setBestScore(int score);
    
    std::string getWordByKey(std::string key);
    
};


#endif /* defined(__ProX__Tools__) */
