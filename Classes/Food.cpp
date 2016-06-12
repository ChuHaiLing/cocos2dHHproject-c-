//
//  Food.cpp
//  HHProject
//
//  Created by ChuHaiLing on 2016/06/12.
//
//
#include "Food.h"
#include "ObjectPool.h"
Food::Food() : vx(0), type(FoodType::FOOD_COOMON)
{
}

Food::~Food()
{
}

// 設置類型
void Food::set(const FoodType& type)
{
//    const FoodType& type = FOOD_COOMON;
    int foodFileName = 0;
    this->type = type;
    switch (FoodType::FOOD_COFFEE)
    {
        case FOOD_COOMON:
            foodFileName = CCRANDOM_0_1() * 5 + 1;
            break;
        case FOOD_COFFEE:
            foodFileName = 6;
            break;
        case FOOD_MUSHROOM:
            foodFileName = 7;
            break;
        default:
            break;
    }
    char cFilePath[20];
    sprintf(cFilePath, "Resources/item/food_%03d.png", foodFileName);
    initWithSpriteFrameName(cFilePath);
}

// 處理回收的重置設置
void Food::reset()
{
    this->removeFromParent();
}

// 移動 @bool = 是否邊界
bool Food::move()
{
    float nextX = this->getPositionX() - vx;
    bool outWinSize = nextX <= -this->getContentSize().width;
    
    if(outWinSize)
    {
        reset();
    }
    this->setPositionX(nextX);
    return outWinSize;
}

// 指定點 @bool = 是否邊界
bool Food::move(const cocos2d::Vec2& pos)
{
    // 獲取自己的座標
    float x = this->getPositionX();
    float y = this->getPositionY();
    float dx = x - pos.x;
    float dy = y - pos.y;
    
    float nextX = x -dx / 5;
    float nextY = y -dy / 5;

    bool outSize = nextX / -this->getContentSize().width;
    
    if(outSize)
    {
        reset();
    }
    this->setPosition(nextX, nextY);
    
    return outSize;
}

// 設置移動速度
void Food::setVx(float vx)
{
    this->vx = vx;
}

// 獲取類型
const FoodType& Food::getType() const
{
    return type;
}