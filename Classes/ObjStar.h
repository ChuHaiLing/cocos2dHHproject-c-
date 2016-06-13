//
//  ObjStar.hpp
//  HHProject
//
//  Created by chu-hailing on 2016/06/13.
//
//

#ifndef __ObjStar_h__
#define __ObjStar_h__

#include "cocos2d.h"
// 引入cocostuido文件, 完成ui環境配置
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
USING_NS_CC;

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
using namespace extension;

class ObjStar : public cocos2d::Node
{
public:
    ObjStar();
    ~ObjStar();
    virtual void onEnter();
    virtual void onExit();
    
    void setShowStar(bool var);
    bool getShowStar();
    
    bool isShow;
};

//
//using namespace cocos2d;
//
//class GameObjStar : public cocos2d::Node
//{
//public:
//    GameObjStar(void);
//    short state;
//    virtual ~GameObjStar(void);
//    virtual void onEnter();
//    virtual void onExit();
//    bool _visable;
//    void set_visable(bool var);
//    bool get_visable();
//};

#endif /* ObjStar_hpp */
