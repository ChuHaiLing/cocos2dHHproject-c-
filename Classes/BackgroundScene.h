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

class BackgroundScene:public cocos2d::Layer
{
public:
    BackgroundScene();
    ~BackgroundScene();
    
    virtual bool init();
    CREATE_FUNC(BackgroundScene);
    
    static cocos2d::Scene* createScene();
    
    // 定時器
    void step(float dt);
    
    // 設置地圖移動的速度
    void setVx(float val);
    
    // 獲取地圖速度
    float getVx() const;
    
    // 靜態的常量
    static const float MOVE_VX_MIN;         // 最小速度
    static const float MOVE_VX_MAX;         // 最大速度
    static const float MAP_WIDTH;           // 地圖的寬度
    
protected:
    cocos2d::Node* layer;
    
    // 單圖移動
    void move(cocos2d::Sprite* bg_1, cocos2d::Sprite* bg_2, float vxScale);
    
private:
    // 移動速度
    float vx;
    
    // 地圖紋理字典
    std::map<std::string, cocos2d::Sprite*> mScrollDict;
};


#endif /* BackgroundScene_hpp */
