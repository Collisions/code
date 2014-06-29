//
//  Tools.cpp
//  ProX
//
//  Created by  YueBinbin on 14-6-17.
//
//

#include "Tools.h"
#include "pugixml.hpp"

static Tools* tools = nullptr;

Tools* Tools::getInstance()
{
    if (!tools)
    {
        tools = new Tools();
    }
    return tools;
}

std::vector<std::string> Tools::splitStr(const std::string &str, const std::string &ch)
{
    std::vector<std::string> vec;
    std::string strTmp = str;
    size_t cutAt;
    while( (cutAt = strTmp.find_first_of(ch)) != strTmp.npos )
    {
        if(cutAt > 0)
        {
            const std::string &temp = strTmp.substr(0, cutAt);
            vec.push_back(temp);
        }
        strTmp = strTmp.substr(cutAt + 1);
    }
    
    if(strTmp.length() > 0)
    {
        vec.push_back(strTmp);
    }
    return vec;
}

int Tools::getBestScore()
{
    
    return UserDefault::getInstance()->getIntegerForKey("SCORE");
}

void Tools::setBestScore(int score)
{
    UserDefault::getInstance()->setIntegerForKey("SCORE", score);
}

std::string Tools::getWordByKey(std::string key)
{
    pugi::xml_document* doc;
    long size;
    std::string filePath = FileUtils::getInstance()->fullPathForFilename("dict.xml");
    //log("=>%s", filePath);
    unsigned char* data = FileUtils::getInstance()->getFileData(filePath, "rb", &size);
    
    if(!data)
    {
        CCLOG("read file error!");
    }
    doc = new pugi::xml_document();
    //pugi::xml_parse_result result =
    doc->load_buffer(data, size);
    CC_SAFE_DELETE(data);
    
    pugi::xml_node root = doc->child("dic");
    
    return root.attribute(key.c_str()).as_string();
}


