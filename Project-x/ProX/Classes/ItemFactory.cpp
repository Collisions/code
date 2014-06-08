//
//  ItemFactory.cpp
//  ProX
//
//  Created by  YueBinbin on 14-6-4.
//
//

#include "ItemFactory.h"
#include "pugixml.hpp"
#include "resource.h"

#define GET_COLOR(color) getColor(str2num(color))
#define SET_COLOR(node, color) node->setColor(getColor(str2num(color)))

static ItemFactory* itemFactory = nullptr;

ItemFactory* ItemFactory::getInstance()
{
    if (!itemFactory)
    {
        itemFactory = new ItemFactory();
        itemFactory->init();
    }
    
    return itemFactory;
}

void ItemFactory::init()
{
    
}

void ItemFactory::createStage(Node &parent, const std::string &filename)
{
    for (auto ritem: itemArr)
    {
        ritem->removeFromParent();
    }
    itemArr.clear();

    
    pugi::xml_document* doc;
    long size;
    std::string filePath = FileUtils::getInstance()->fullPathForFilename(filename);
    unsigned char* data = FileUtils::getInstance()->getFileData(filePath, "rb", &size);
    
    if(!data)
    {
        CCLOG("read file error!");
        createStage(parent, "stage_1.xml");
    }
    
    doc = new pugi::xml_document();
    //pugi::xml_parse_result result =
    doc->load_buffer(data, size);
    CC_SAFE_DELETE(data);
    
    pugi::xml_node root = doc->child("stage");
    
    auto bg = parent.getChildByTag(BG);
    auto ground = parent.getChildByTag(GROUND);
    auto player = parent.getChildByTag(PLAYER);
    SET_COLOR(bg, root.attribute("bgColor").as_string());
    SET_COLOR(ground, root.attribute("gColor").as_string());
    SET_COLOR(player, root.attribute("boxColor").as_string());
    
    pugi::xml_node items = root.child("items");
    
    for (pugi::xml_node item = items.child("item"); item;  item = item.next_sibling("item"))
    {
        
        auto ite = LayerColor::create(Color4B::RED, str2num(item.attribute("width").as_string()), str2num(item.attribute("height").as_string()));
        setPositionByStr(*ite, item.attribute("position").as_string());
        SET_COLOR(ite, item.attribute("color").as_string());
        ite->setTag(str2num(item.attribute("tag").as_string()));
        parent.addChild(ite);
        itemArr.pushBack(ite);
        
        pugi::xml_node action = item.child("action");
        if (action) {
            createAction(*ite, str2num(action.attribute("type").as_string()),str2num(action.attribute("dura").as_string()), action.attribute("para").as_string());
        }
    }
}

Color3B ItemFactory::getColor(int color)
{
    switch (color) {
        case 1:
            return Color3B::BLACK;
        case 2:
            return Color3B::RED;
        case 3:
            return Color3B::YELLOW;
        case 4:
            return Color3B::ORANGE;
        case 5:
            return Color3B::MAGENTA;
        case 6:
            return Color3B::GREEN;
        case 7:
            return Color3B::GRAY;
        case 8:
            return Color3B::BLUE;
        case 9:
            return Color3B::WHITE;
		case 10:
			return Color3B::RBLUE;
        default:
            return Color3B::WHITE;
    }
}

int ItemFactory::str2num(const std::string &str)
{
    int f;
    std::stringstream ff(str);
    ff>>f;
    return f;
}

void ItemFactory::setPositionByStr(Node &node, const std::string &pos)
{
    unsigned long index = pos.find_first_of(",");
    
    std::string www = pos.substr(0, index);
    std::string hhh = pos.substr(index + 1, pos.length());
    
    int width,height;
    std::stringstream ww(www);
    ww>>width;
    std::stringstream hh(hhh);
    hh>>height;
    
    auto size = Director::getInstance()->getVisibleSize();
    
    node.setPosition(Point(size.width * width/100, size.height * height/100 + 150));
    
}

void ItemFactory::createAction(Node &node, int type, int dura, const std::string &para)
{
    
    if(type == 1)
    {
        unsigned long index = para.find_first_of(",");
        
        std::string www = para.substr(0, index);
        std::string hhh = para.substr(index + 1, para.length());
        
        int width,height;
        std::stringstream ww(www);
        ww>>width;
        std::stringstream hh(hhh);
        hh>>height;

        auto size = Director::getInstance()->getVisibleSize();

        auto move = MoveBy::create(dura, Point(size.width * width/100, size.height * height/100));
        auto move_back = move->reverse();
        auto seq = Sequence::create(move, move_back, NULL);
        auto rep = RepeatForever::create(seq);
        node.runAction(rep);
    }
    
}




