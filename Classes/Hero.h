//
//  Hero.hpp
//  HHProject
//
//  Created by ChuHaiLing on 2016/06/05.
//
//

#ifndef __Hero_h__
#define __Hero_h__
#include<string>
#include<list>
using namespace std;

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

class Hero:public cocos2d::Sprite
{
public:
    Hero();
    ~Hero();
    
    virtual bool init();
    CREATE_FUNC(Hero);
    
    static cocos2d::Scene* createScene();
    
    // 當手指觸碰螢幕時的跟隨
    void folloTounh(const cocos2d::Vec2& pos);
    
    // 撞擊障礙物
    void hit();
    
    // （當ＨＰ <＝ 0）墜落
    void fall();
    
protected:
    void addFlyAction();
    
    // 停止手指觸碰跟隨
    bool hitting;
};

#endif /* Hero_h */
