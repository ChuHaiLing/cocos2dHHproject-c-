//
//  StartScene.cpp
//  HHProject
//
//  Created by ChuHaiLing on 2016/06/04.
//
//

#include "StartScene.h"

StartScene::StartScene()
{
    
}

StartScene::~StartScene()
{
    
}

// 創建場景
Scene* StartScene::createScene()
{
    // 創建一個自動釋放的場景對象
    auto startScene = Scene::create();
    
    // 創建一個自動釋放的畫面層對象。
    auto layer = StartScene::create();
    
    // 把創建的畫面層添加到場景中。
    startScene->addChild(layer);
    
    // 返回這個創建的場景。
    return startScene;
}

// 場景的初始化。
bool StartScene::init()
{
    if(!Layer::init())  // 父類的初始化。
    {
        return false;   // 失敗了話返回false
    }
    
    //    auto layer = CSLoader::createNode("StartScene.csb");
    //    addChild(layer);
    
    // 創建指定的startScene。
    layer = CSLoader::createNode("StartScene.csb");
    this->addChild(layer);
    
    // dynamic_cast<<#type#>>(<#expression#>) : 類型轉換方式。该运算符把expression转换成type-id类型的对象。Type-id 必须是类的指针、类的引用或者void*
    auto* btnPlay = dynamic_cast<Button*>(layer->getChildByName("play_btn"));                   // playGame btn
    auto* btnAbout = dynamic_cast<Button*>(layer->getChildByName("about_btn"));                 // about btn
    auto* boxSound = dynamic_cast<CheckBox*>(layer->getChildByName("checkBox_btn"));            // checkBox btn
    
    // 按鈕的監聽。
    // addTouchEventListener (Ref *target 監聽對象, SEL_TouchEvent selector 方法) : 设置触摸事件的响应选择器和目标。
    // CC_CALLBACK
    // CC_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
    // __selector__ : 綁定要調回的函數名，注意要加上命名空間：函數名。
    // __target__ : 綁定一個對象。
    // std::placeholders::_1 : 綁定的函數裡除了第1個參數之外的參數，就是調用函數傳餐時要傳第1個參數，如果__select__後面有參數，則在用CC_CALLBACK時要綁定。
    btnPlay->addTouchEventListener(CC_CALLBACK_2(StartScene::ButtonOnTouchListener, this));
    btnAbout->addTouchEventListener(CC_CALLBACK_2(StartScene::ButtonOnTouchListener, this));
    
    // 因為Play和About都是同樣使用一個監聽方法，因此在此處使用枚舉(enum)來指定標籤(tag)後，再由方法內分配工作。
    btnPlay->setTag(UIButtonTag::BTN_PLAY_GAME);
    btnAbout->setTag(UIButtonTag::BTN_ABOUT);
    
    // checkBox的監聽
    boxSound->addEventListener(CC_CALLBACK_2(StartScene::CheckBoxOnTouncListener, this));
    
    //    // sound動畫
        addSoundAnime();
    
    // Move to point
    addHeroAndBtnAction();
    
    // 返回初始化的創建。
    return true;
}

// button 事件回調函數。
void StartScene::ButtonOnTouchListener(cocos2d::Ref* target, cocos2d::ui::Widget::TouchEventType type)
{
    // 如果type不屬於任何值，跳出此方法。
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED) return;
    
    // 標籤的賦值。
    // dynamic_cast<<#type#>>(<#expression#>) : 類型轉換方式。
    int tag = dynamic_cast<Node*>(target)->getTag();
    
    switch (tag)
    {
        case StartScene::BTN_PLAY_GAME:     // play game button
        {
            // Scene轉移 fade效果
            auto* changeAct1 = cocos2d::TransitionFade::create(0.5f, MainScene::createScene());
            // Scene轉移
            Director::getInstance()->replaceScene(changeAct1);
            Director::getInstance()->replaceScene(MainScene::createScene());
            log("paly");
            break;
        }
        case StartScene::BTN_ABOUT:         // about game button
        {
//            auto* changeAct2 = cocos2d::TransitionFlipX::create(0.5f, aboutGameScene::createAboutGameScene());
//            Director::getInstance()->replaceScene(changeAct2);
            log("about");
            break;
        }
    }
}

// checkBox 事件回調函數
void StartScene::CheckBoxOnTouncListener(cocos2d::Ref* target, cocos2d::ui::CheckBox::EventType type)
{
    // 選中 selected
    if(type != CheckBox::EventType::SELECTED)
    {
        //   log("open sound");
    }
    // 非選中 unSelected
    else if(type != CheckBox::EventType::UNSELECTED)
    {
        // log("clase sound");
    }
}

// 英雄進場動畫及按鈕動畫
void StartScene::addHeroAndBtnAction()
{
    // get Win Size
    Size winSize = Director::getInstance()->getWinSize();
    
    // Move to point
    auto* imgHero = dynamic_cast<Sprite*>(layer->getChildByName("img_hero_move"));
    
    // 動作設置
    auto* toMove = MoveTo::create(0.5f,                                         // 速度
                                  Vec2(winSize.width / 4, winSize.height / 2)); // 移動的目標
    
    // sin曲線關數的使用
    auto* callback = CallFunc::create([=]()
                                      {
                                          // 上下動畫
                                          imgHero->runAction(createSineAction(1.0f, 100));
                                      });
    
    // 將toMove和callback製作成動畫列表
    auto* seq = Sequence::create(toMove, callback, nullptr);
    
    // 生成
    imgHero->runAction(seq);
    
    // 按鈕動畫
    auto* btnPlay = dynamic_cast<Button*>(layer->getChildByName("play_btn"));
    auto* btnAbout = dynamic_cast<Button*>(layer->getChildByName("about_btn"));
    
    btnPlay->runAction(createSineAction(1.0f, 4));
    btnAbout->runAction(createSineAction(1.0f, 4));
}

// SINE 上下漂浮的動畫
cocos2d::Action* StartScene::createSineAction(float time, float dist)
{
    // 沒有使用sine動畫前 = auto* downAct = MoveBy::create(time, Vec2(0, -dist));
    auto* downAct = EaseSineInOut::create(MoveBy::create(time, Vec2(0, -dist)));
    auto* upAct = EaseSineInOut::create(MoveBy::create(time, Vec2(0, dist)));
    
    auto* seq = Sequence::create(downAct, upAct, nullptr);
    auto* rep = RepeatForever::create(seq);
    return rep;
}


// sound圖動畫。
void StartScene::addSoundAnime()
{
    // 創建動畫。
    Vector<SpriteFrame*> frameList(3);
    auto spriteFrameCache = SpriteFrameCache::getInstance();
   
    char fileName[100] = {0};
   
    // 因為有3張圖，因此此處用for循環。
    for(int i = 1; i <= 3; i++)
    {
        sprintf(fileName, "Resources/textures/img_snd_on_%03d.png", i);
    
        SpriteFrame *frame = SpriteFrame::create(fileName, Rect(0, 0, 40, 40));
    
        // 加入SpriteFrameCache中
        spriteFrameCache->addSpriteFrame(frame, fileName);
        frameList.pushBack(frame);
    }
    
    // 動畫腳本。
    auto* anim = Animation::createWithSpriteFrames(frameList, 0.1f);
    
    // 動畫
    auto* animCreate = Animate::create(anim);
    
    // 重複播放
    auto* rep = RepeatForever::create(animCreate);
    
    //
    auto* boxSound = dynamic_cast<CheckBox*>(layer->getChildByName("checkBox_btn"));
    //boxSound->loadTextureBackGround("Resources/res/Resources/textures/img_snd_on_001.png");
    
    //
    auto* sp = Sprite::create();
    
    // 創圖
    boxSound->addChild(sp);
    
    // 錨點
    sp->setAnchorPoint(Vec2::ZERO);
    
    sp->runAction(rep);
}
