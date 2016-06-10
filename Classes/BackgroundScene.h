//
//  BackgroundScene.hpp
//  HungryHeroProject
//
//  Created by ChuHaiLing on 2016/06/04.
//
//

#ifndef __BackgroundScene_h__
#define __BackgroundScene_h__

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

#define MAP_1_Tag 1
#define MAP_2_Tag 2

class BackgroundScene:public cocos2d::Layer
{
public:
    BackgroundScene();
    ~BackgroundScene();
    
    virtual bool init();
    CREATE_FUNC(BackgroundScene);
    void onExit();          // 離開
    static cocos2d::Scene* createScene();
    
protected:
    cocos2d::Node* layer;
    
private:
    void update(float time);        // 更新速度
//    virtual void onExit();          // 離開
    static const int MOVE_X_SPEED;  // 捲軸速度
};


#endif /* BackgroundScene_hpp */
