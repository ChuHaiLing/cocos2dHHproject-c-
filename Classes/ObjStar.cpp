//
//  ObjStar.cpp
//  HHProject
//
//  Created by chu-hailing on 2016/06/13.
//
//

#include "ObjStar.h"

ObjStar::ObjStar()
{
}

ObjStar::~ObjStar()
{
}

void ObjStar::onEnter()
{
    Node::onEnter();
    
    // 初始化
    this->setContentSize(Size(35, 35));
    auto* star = Sprite::create("item/food_004.png");
    star->setScale(0.5);
    isShow = true;
    addChild(star, 1);
}

void ObjStar::setShowStar(bool var)
{
    isShow = var;
    this->setShowStar(var);
}

bool ObjStar::getShowStar()
{
    return isShow;
}

void ObjStar::onExit()
{
    Node::onExit();
}

//void GameObjStar::set_visable(bool var){
//    _visable = var;
//    this->setVisible(var);
//}
//bool GameObjStar::get_visable(){
//    return _visable;
//}

//void GameObjStar::onEnter(){
//    CCNode::onEnter();
//    //星星初始化
//    this->setContentSize(CCSizeMake(36.5,35.5));
//    CCSprite* star = CCSprite::create("star.png");
//    star->setScale(0.5);
//    _visable = true;
//    addChild(star,1);
//}
//void GameObjStar::onExit(){
//    CCNode::onExit();
//}