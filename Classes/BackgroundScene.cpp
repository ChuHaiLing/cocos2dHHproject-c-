//
//  BackgroundScene.cpp
//  HungryHeroProject
//
//  Created by ChuHaiLing on 2016/06/04.
//
//

#include "BackgroundScene.h"

BackgroundScene::BackgroundScene()
{
}

BackgroundScene::~BackgroundScene()
{
}

//
const float BackgroundScene::MOVE_VX_MIN = 10;
const float BackgroundScene::MOVE_VX_MAX = 30;
const float BackgroundScene::MAP_WIDTH = 1334;      // 1334

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
    Layer::init();
//    if(!Layer::init())
//    {
//        return false;
//    }
    
    // 捲軸地圖紋理
    mScrollDict["bg_001_1"] = Sprite::createWithSpriteFrameName("Resources/background/bg_001.png");
    mScrollDict["bg_001_2"] = Sprite::createWithSpriteFrameName("Resources/background/bg_001.png");
    
    mScrollDict["bg_002_1"] = Sprite::createWithSpriteFrameName("Resources/background/bg_002.png");
    mScrollDict["bg_002_2"] = Sprite::createWithSpriteFrameName("Resources/background/bg_002.png");
    
    mScrollDict["bg_003_1"] = Sprite::createWithSpriteFrameName("Resources/background/bg_003.png");
    mScrollDict["bg_003_2"] = Sprite::createWithSpriteFrameName("Resources/background/bg_003.png");

    mScrollDict["bg_004_1"] = Sprite::createWithSpriteFrameName("Resources/background/bg_004.png");
    mScrollDict["bg_004_2"] = Sprite::createWithSpriteFrameName("Resources/background/bg_004.png");
    
    this->addChild(mScrollDict["bg_001_1"], 1);
    this->addChild(mScrollDict["bg_001_2"], 1);
    
    this->addChild(mScrollDict["bg_002_1"], 2);
    this->addChild(mScrollDict["bg_002_2"], 2);
    
    this->addChild(mScrollDict["bg_003_1"], 3);
    this->addChild(mScrollDict["bg_003_2"], 3);
    
    this->addChild(mScrollDict["bg_004_1"], 4);
    this->addChild(mScrollDict["bg_004_2"], 4);
    
    mScrollDict["bg_001_1"]->setAnchorPoint(Vec2::ZERO);
    mScrollDict["bg_001_2"]->setAnchorPoint(Vec2::ZERO);
    
    mScrollDict["bg_002_1"]->setAnchorPoint(Vec2::ZERO);
    mScrollDict["bg_002_2"]->setAnchorPoint(Vec2::ZERO);
    
    mScrollDict["bg_003_1"]->setAnchorPoint(Vec2::ZERO);
    mScrollDict["bg_003_2"]->setAnchorPoint(Vec2::ZERO);
    
    mScrollDict["bg_004_1"]->setAnchorPoint(Vec2::ZERO);
    mScrollDict["bg_004_2"]->setAnchorPoint(Vec2::ZERO);
    
    mScrollDict["bg_001_2"]->setPositionX(MAP_WIDTH);
    mScrollDict["bg_002_2"]->setPositionX(MAP_WIDTH);
    mScrollDict["bg_003_2"]->setPositionX(MAP_WIDTH);
    mScrollDict["bg_004_2"]->setPositionX(MAP_WIDTH);
    
    vx = MOVE_VX_MIN;
    
    layer = CSLoader::createNode("BackgroundScene.csb");
    this->addChild(layer);
    
    return true;
}

// 定時器
void BackgroundScene::step(float dt)
{
    move(mScrollDict["bg_001_1"], mScrollDict["bg_001_2"], 0.5f);
    move(mScrollDict["bg_002_1"], mScrollDict["bg_002_2"], 0.6f);
    move(mScrollDict["bg_003_1"], mScrollDict["bg_003_2"], 0.8f);
    move(mScrollDict["bg_004_1"], mScrollDict["bg_004_2"], 1.0f);
}

// 設置地圖移動的速度
void BackgroundScene::setVx(float val)
{
    this->vx = val;
}

// 獲取地圖速度
float BackgroundScene::getVx() const
{
    return vx;
}

// 單圖移動
void BackgroundScene::move(cocos2d::Sprite* bg_1, cocos2d::Sprite* bg_2, float vxScale)
{
    log("move");
    float vx_1 = bg_1->getPositionX() - vx * vxScale;
    float vx_2 = bg_2->getPositionX() - vx * vxScale;
    
    // 出界的場合
    if(vx_1 <= -MAP_WIDTH)
    {
        vx_1 = vx_2 + MAP_WIDTH;
    }
    else if(vx_2 <= -MAP_WIDTH)
    {
        vx_2 = vx_1 + MAP_WIDTH;
    }
    
    bg_1->setPositionX(vx_1);
    bg_2->setPositionX(vx_2);
}