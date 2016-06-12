//
//  MainGameScene.hpp
//  HungryHeroProject
//
//  Created by ChuHaiLing on 2016/05/29.
//
//

#ifndef __MainScene_h__
#define __MainScene_h__

#include "cocos2d.h"
#include "BackgroundScene.h"
#include "Hero.h"
#include "Food.h"
#include "ObjectPool.h"

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

class MainScene:public cocos2d::Layer
{
public:
    MainScene();
    ~MainScene();
    
    virtual bool init();
    
    // 觸屏事件的註冊
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    // 
    virtual void onEnterTransitionDidFinish();
    
    CREATE_FUNC(MainScene);
    
    static cocos2d::Scene* createScene();
    
    // 更新遊戲數據視圖
    void updateDateView();
    
protected:
    cocos2d::Node* layer;
    cocos2d::ui::CheckBox* boxSound;
    cocos2d::ui::TextBMFont* fontLive;
    cocos2d::ui::TextBMFont* fontDist;
    cocos2d::ui::TextBMFont* fontScore;
    
    BackgroundScene* mBackground;
    Hero* mHero;
    
    // checkBox 事件回調函數
    void CheckBoxOnTouncListener(cocos2d::Ref* target, cocos2d::ui::CheckBox::EventType type);
  
    // 註冊事件
    void addAllEventListener();
    
    // 遊戲時間循環
    void gameStep(float dt);
    
    // 開始遊戲
    void startGame();
    
    // 英雄進場
    void heroInSceneAction();
    
    // 抖屏
    void shakeWindows(float dt);
    
    // touchPos設置於屏幕正中央 center
    cocos2d::Vec2 touchPos;
    
    // 螢幕的Size
    cocos2d::Size winSize;
    
    float shakeTime = 0.0f;
    
    //
    ObjectPool<Food>* mObjectPool;
    
private:
    static const float START_POINT;
};

#endif /* MainGameScene_hpp */
