//
//  BackgroundScene.cpp
//  HungryHeroProject
//
//  Created by ChuHaiLing on 2016/06/04.
//
//

#include "BackgroundScene.h"

// 捲軸滑動速度的賦予值
const int BackgroundScene::MOVE_X_SPEED = 10;

BackgroundScene::BackgroundScene()
{
}

BackgroundScene::~BackgroundScene()
{
}

Scene* BackgroundScene::createScene()
{
    // create gameScene
    auto* backgroundScene = Scene::create();
    
    // 創建一個自動釋放的畫面層對象。
    auto* layer = BackgroundScene::create();
    
    // 把layer添加到場景中
    backgroundScene->addChild(layer);
    
    // 返回這個創建的場景
    return backgroundScene;
}

bool BackgroundScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    // 獲得視窗大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // get script
    auto map1 = Sprite::create("Resources/background/bg_001.png");
    auto map2 = Sprite::create("Resources/background/bg_001.png");
    
    // 設置第一張圖片的位置
    map1->setPosition(ccp(map1->getContentSize().width/2 + origin.x,
                          map1->getContentSize().height/2 + origin.y));
    
    // 第二張圖片的位置於第一張的位置之後( x + x.size)
    map2->setPosition(ccp(map2->getContentSize().width/2 + origin.x + map2->getContentSize().width,
                          map2->getContentSize().height/2 + origin.y));
    
    this->addChild(map1, 0, MAP_1_Tag);
    this->addChild(map2, 0, MAP_2_Tag);
    this->scheduleUpdate();
    
    return true;
}

// scrore update
void BackgroundScene::update(float time)
{
    // windo size
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 可視原點的座標
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // get script
    auto temMap1 = this->getChildByTag(MAP_1_Tag);
    auto temMap2 = this->getChildByTag(MAP_2_Tag);
    
    // pos = x -10 -> make score
    temMap1->setPositionX(temMap1->getPositionX() - MOVE_X_SPEED);
    temMap2->setPositionX(temMap2->getPositionX() - MOVE_X_SPEED);
    
    // 當圖片1的位置 < 可視原點，
    if(temMap1->getPositionX() + temMap1->getContentSize().width/2 <= origin.x)
    {
        // 偏移 ＝ 圖片的x軸 ＋ 寬 - 可視圓點的x軸
        float offset = temMap1->getPositionX() + temMap1->getContentSize().width/2 - origin.x;
        
        // 設置圖片1的位置到圖片2之後
        // ccp(a, b) = ccpoint(x, y)：既可以表示座標點，又可以表示一個向量。
        // getContentSize() = 此函數來獲得原始節點的大小，只是邏輯尺寸，不是像素大小。
        // x = (getContentSize()原始節點的大小)寬 / 2 ＋ 可視點的寬 ＋ ()
        temMap1->setPosition(ccp(temMap1->getContentSize().width / 2 +
                                 origin.x + visibleSize.width + offset,
                                 visibleSize.height/2 + origin.y));
    }
    
    // 當圖片2的位置 < 可視原點
    if(temMap2->getPositionX() + temMap2->getContentSize().width/2 <= origin.x)
    {
        float offset = temMap2->getPositionX() + temMap2->getContentSize().width/2 - origin.x;
        
        temMap2->setPosition(ccp(temMap2->getContentSize().width/2 +
                                 origin.x + visibleSize.width + offset,
                                 visibleSize.height/2 + origin.y));
    }
}

// 停止捲軸滑動
void BackgroundScene::onExit()
{
    this->unscheduleUpdate();
    CCLayer::onExit();
}