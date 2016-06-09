//
//  Hero.cpp
//  HHProject
//
//  Created by ChuHaiLing on 2016/06/05.
//
//

#include "Hero.h"
Hero::Hero()
{

}

Hero::~Hero()
{
    
}

Scene* Hero::createScene()
{
    // create gameScene
    auto* heroScene = Scene::create();
    
    // 創建一個自動釋放的畫面層對象。
    auto* layer = Hero::create();
    
    // 把layer添加到場景中
    heroScene->addChild(layer);
    
    // 返回這個創建的場景
    return heroScene;
}

bool Hero::init()
{
    // 手指的跟隨
    hitting = false;
    
    Sprite::init();
    
    addFlyAction();
    
    return true;
}

void Hero::addFlyAction()
{
    
//    auto hero = Sprite::create("Resources/hero/fly_0001.png");
//    this->addChild(hero, 2);
    Vector<SpriteFrame*>frameList;
    
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    
    char fileName[256] = {0};
    
    for(int i = 1; i <= 20; i++)
    {
        sprintf(fileName, "Resources/hero/fly_%04d.png", i);
        
        // 155, 77是图片的大小，貌似这样直接设定是不好的；但是还必须提供这个参数
        // 应该给这个Rect参数提供一个默认参数，默认加载整个图片
        SpriteFrame *frame = SpriteFrame::create(fileName, Rect(0, 0, 155, 77));
        
        // 加入SpriteFrameCache中
        spriteFrameCache->addSpriteFrame(frame, fileName);
        frameList.pushBack(frame);
        
        
//        auto* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
//        frameList.pushBack(frame);
    }
    
    // 參數為播放速度
    auto* anim = Animation::createWithSpriteFrames(frameList, 0.05f);
    auto* ani = Animate::create(anim);
    auto* rep = RepeatForever::create(ani);
    
    this->runAction(rep);
}

void Hero::folloTounh(const cocos2d::Vec2& pos)
{
    if(hitting)
    {
        return;
    }
    // 計算手指觸碰點與hero之間的夾角
    // 距離差 = 英雄位置 - 手指所在的距離差
    float dx = pos.x - this->getPositionX();
    float dy = pos.y - this->getPositionY();
    
    // 角度的弧度的表示（求出來的值必須加上 負號，才能獲得正確值）
    float raduiAngle = -std::atan2(dy, dx);
    
    // 求出角度
    float angle = raduiAngle * 180 / 3.14;
    
    // 讓英雄弧度保持在45度或-45度
    if(angle <= -45)
    {
        angle = -45;
    }
    else if (angle >= 45)
    {
        angle = 45;
    }
    
    //
    this->setRotation(angle);
    
    // (平均)勻減速：向手指觸碰點高度進行均減速運動。
    this->setPositionY(this->getPositionY() + dy / 10);
}
    
// 撞擊障礙物
void Hero::hit()
{
    // 向下沉與翻根斗同時進行
    hitting = true;
    
    auto* rotAct = RotateBy::create(0.5f, 999);
    this->runAction(rotAct);
    
    auto* moveAct = MoveBy::create(0.5f, Vec2(0, -100));
    this->runAction(moveAct);
    
    auto* callback = CallFunc::create([=]()
    {
        hitting = false;
    });
    
    auto* seq = Sequence::create(DelayTime::create(0.5f), callback, nullptr);
    this->runAction(seq);
}

// （當ＨＰ <＝ 0）墜落
void Hero::Hero::fall()
{
    hitting = true;
    auto* rotAct = RotateBy::create(0.5f, 999);
    this->runAction(rotAct);
    
    auto* moveAct = MoveTo::create(0.5f, Vec2(this->getPositionX(), -200));
    this->runAction(moveAct);
}
