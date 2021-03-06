//
//  MainGameScene.cpp
//  HungryHeroProject
//
//  Created by ChuHaiLing on 2016/05/29.
//
//

#include "MainScene.h"

// 進場位置的賦值
const float MainScene::START_POINT = 200;

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

Scene* MainScene::createScene()
{
    // create gameScene
    auto* mainGameScene = Scene::create();
    
    // 創建一個自動釋放的畫面層對象。
    auto* layer = MainScene::create();
    
    // 把layer添加到場景中
    mainGameScene->addChild(layer);
    
    // 返回這個創建的場景
    return mainGameScene;
}

bool MainScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    // 滾動背景
    mBackground = BackgroundScene::create();
    this->addChild(mBackground, 0);
    
    
    // 背景的停止更新
//    mBackground->onExit();
    
    // mainlayer的生成
    layer = CSLoader::createNode("MainScene.csb");
    this->addChild(layer);
    
    // 賦值
    boxSound = dynamic_cast<CheckBox*>(layer->getChildByName("checkBox_btn"));
    fontLive = dynamic_cast<TextBMFont*>(layer->getChildByName("leves_bmp"));
    fontDist = dynamic_cast<TextBMFont*>(layer->getChildByName("distance_bmp"));
    fontScore = dynamic_cast<TextBMFont*>(layer->getChildByName("score_bmp"));
    
    // Hero設置
    mHero = Hero::create();
    this->addChild(mHero, 2);
    
    // Hero的初始位置為 螢幕外, 高為螢幕的一半
    mHero->setPosition(-(START_POINT), winSize.height / 2);
    
    // 螢幕位置賦值
    winSize = Director::getInstance()->getWinSize();
    
    // 觸碰點的賦值（初始為正中央）
    touchPos = Vec2(winSize.width / 2, winSize.height / 2);
    
    // 更新遊戲數據視圖
    updateDateView();
    
    // 註冊事件
    addAllEventListener();
    
    // 對象池的初始化
    mObjectPool = ObjectPool<Food>::getInstance();

    return true;
}

// 更新遊戲數據視圖
void MainScene::updateDateView()
{
    int value = 5;
    char strValue[20];
    
    // 生命值的賦予值
    sprintf(strValue, "%d", value);
    fontLive->setString(strValue);
    
    // 距離的值
    value = 1000;
    sprintf(strValue, "%d", value);
    fontDist->setString(strValue);
    
    // 積分
    value = 90;
    sprintf(strValue, "%d", value);
    fontScore->setString(strValue);
}

// 註冊監聽事件
void MainScene::addAllEventListener()
{
    // 賦值
    boxSound->addEventListener(CC_CALLBACK_2(MainScene::CheckBoxOnTouncListener, this));
    
    // 觸屏事件偵聽
    auto* touchEvent = EventListenerTouchOneByOne::create();
    
    // 綁定
    touchEvent->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    touchEvent->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    touchEvent->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    
    // 將事件註冊。通過director來使用事件開發者（getEventDispatcher），在使用 addEventListenerWithSceneGraphPriority（對象, 節點）。此處的節點的作用為，最主要的是將對象與節點關聯起來，也就是說如果mainGameScene被釋放掉時，將會由事件管理者將此事件給摧毀掉。
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvent, this);
}

// check Box事件回調函數
void MainScene::CheckBoxOnTouncListener(cocos2d::Ref* target, cocos2d::ui::CheckBox::EventType type)
{
    
}

// 此處的返回值是當 onTouchBegan 被觸發後，是不是能進行到 onTouchMoved 或是 onTouchEnded
// 如果為falst了話將會中斷於 onTouchBegan
bool MainScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    // 獲取當前觸碰的位置座標
//    auto touchPos = touch->getLocation();
    touchPos = touch->getLocation();

//    log("onTouchBegan x:%f y:%f", touchPos.x, touchPos.y);
    
    // 螢幕抖動的時間賦值
    //shakeTime = 2.0f;
    
    return true;
}

// 手指在螢幕上移動時
void MainScene::onTouchMoved(Touch *touch, Event *unused_event)
{
    //auto touchPos = touch->getLocation();
    touchPos = touch->getLocation();
    //log("onTouchMoved x:%f y:%f", touchPos.x, touchPos.y);
}

// 手指離開螢幕時
void MainScene::onTouchEnded(Touch *touch, Event *unused_event)
{
    touchPos = touch->getLocation();
    //auto touchPos = touch->getLocation();
}

// 遊戲時間循環(gameUpdate)
void MainScene::gameStep(float dt)
{    
    // hero的移動更新
    mHero->folloTounh(touchPos);
    
    shakeWindows(dt);
}

// 開始遊戲前的過場時間
void MainScene::startGame()
{
    // 定時的調用此函數(開始遊戲時間主循環)
    this->schedule(SEL_SCHEDULE(&MainScene::gameStep),
                                0.02f);                     // 循環時間
    
    
    
    
    
    // test
    // 古いやり方で
    auto* stars1 = Array::createWithCapacity(5);
    auto* stars2 = Array::createWithCapacity(5);
    
    for(int i = 0; i < 5; i ++)
    {
        ObjStar* objStar = new ObjStar();
        objStar->setPosition(ccp(100 * i, 200));
        
        stars1->addObject(objStar);
        objStar->addChild(objStar, 7);
        
//        obj = new GameObjStar();
//        obj->setPosition(ccp(172 + 192 * i, 350));
//        stars2->addObject(obj);
//        bg2->addChild(obj,1);
    }
    stars1->retain();
    stars2->retain();
    
    
    
    
}

// onEnterTransitionDidFinish ＝ 在完全進入場景後才開始函數內容
void MainScene::onEnterTransitionDidFinish()
{
    //startGame();
    heroInSceneAction();                                    // 進場動畫
}

// Hero進場動畫
void MainScene::heroInSceneAction()
{
    auto* toAct = EaseSineOut::create(MoveTo::create        // EaseSineOut 靠近目標點時速度緩慢
                                      (2.0f,                // 過程時間
                                       Vec2(winSize.width / 4, winSize.height / 2)));   // 移動到的位置
    
    // 回調函數，等待進場0.2秒後，才開始進行遊戲
    auto* callback = CallFunc::create([=]()
    {
        startGame();                                        // 過場時間, 此時無法對角色進行控制
        addAllEventListener();                              // 開始註冊事件（觸碰螢幕等等）
    });
    
    // 生成一整串動畫，
    mHero->runAction(Sequence::create(toAct,                // 入場動畫
                                      callback,             // 回調函數
                                      nullptr));            // 空
}

// 螢幕的震動
void MainScene::shakeWindows(float dt)
{
    if(shakeTime <= 0)
    {   // 座標歸零
        this->setPosition(0, 0);
        return;
    }
    else
    {
        log("shake");
        shakeTime -= dt;
    }
    // 隨機生成亂數
    float dx = CCRANDOM_0_1() * 8;
    float dy = CCRANDOM_0_1() * 8;
    
    this->setPosition(dx, dy);
}