//
//  StartScene.hpp
//  HHProject
//
//  Created by ChuHaiLing on 2016/06/04.
//
//

#ifndef __StartScene_h__
#define __StartScene_h__

#include "cocos2d.h"
#include "MainScene.h"
//#include "aboutGameScene.h"

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


class StartScene:public cocos2d::Layer
{
    // 按鈕的標籤 button tag。
    typedef enum
    {
        BTN_PLAY_GAME,          // play game
        BTN_ABOUT               // about game
    }UIButtonTag;
    
public:
    StartScene();
    ~StartScene();
    
    virtual bool init();        // 初始化
    CREATE_FUNC(StartScene);    // CREATE_FUNC : 用来为一个类似CCLayer类的特定的类增加一个create函数
    
    static cocos2d::Scene* createScene();
    
protected:
    // button事件回調函數
    void ButtonOnTouchListener(cocos2d::Ref* target, cocos2d::ui::Widget::TouchEventType type);
    
    // checkBox 事件回調函數
    void CheckBoxOnTouncListener(cocos2d::Ref* target, cocos2d::ui::CheckBox::EventType type);
    
    // bgm的聲音動畫
    void addSoundAnime();
    
    // 英雄進場及場景動畫
    void addHeroAndBtnAction();
    
    // sine動畫
    cocos2d::Action* createSineAction(float time, float dist);
    
    cocos2d::Node* layer;
};

#endif /* StartScene_hpp */
