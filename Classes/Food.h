//
//  Food.hpp
//  HHProject
//
//  Created by ChuHaiLing on 2016/06/12.
//
//

#ifndef __Food_h__
#define __Food_h__

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

typedef enum
{
    FOOD_COOMON = 5,
    FOOD_COFFEE,        // speed up
    FOOD_MUSHROOM       //
}FoodType;

class Food:public cocos2d::Sprite
{
public:
    Food();
    ~Food();
    
    CREATE_FUNC(Food);
    
    // 設置類型
    void set(const FoodType& type = FoodType::FOOD_COOMON);
    
    // 處理回收的重置設置
    void reset();
    
    // 移動 @bool = 是否邊界
    bool move();
    
    // 指定點 @bool = 是否邊界
    bool move(const cocos2d::Vec2& pos);
    
    // 設置移動速度
    void setVx(float vx);
    
    // 獲取類型
    const FoodType& getType() const;
    
    FoodType type;
    
private:
    int vx;

};

#endif /* Food_hpp */
