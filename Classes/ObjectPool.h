//
//  ObjectPool.hpp
//  HHProject
//
//  Created by ChuHaiLing on 2016/06/11.
//
//

#ifndef __ObjectPool_h__
#define __ObjectPool_h__

#include "Food.h"
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
#include <queue>
#include <vector>

// 模板，特性為靜態多態。
// 類型確定後可以定義出各種不同的對象（對象的數據成員值各不相同，而且內據不同的內存區域）
// 模板確定後，依據給定的模板參數的不同類型，可以定義版本的數據類型
template<class T>

class ObjectPool
{
public:
    ~ObjectPool();
    
    static ObjectPool<T>* getInstance();            // 靜態方法

    // 利用返回模板類型的對象的指針來獲取對象（能夠在對象池中獲得對象的接口
    T* takeout();
    
    // 回收對象
    void recycle(T* obj);
    
private:
    ObjectPool(){};                                     // 函數重載
    ObjectPool(const ObjectPool<T>& src){};             // 函數重載
    ObjectPool<T>& operator=(const ObjectPool<T>& src){};
    
    static ObjectPool<T>* instance;                     // 靜態變量
    void allocate();                                    // 申請內存塊，創建預備對象（創建指定個數的對象內存）
    void disposeObjectArray(std::vector<T*>* objArrary);// 釋放內存塊
    std::queue<T*>mPoolList;                            // 當有申請時（allocate），獲取此空閒列表
    std::vector<std::vector<T*>*>mAllObjectList;        // 內存快管理池
    
    // 靜態常量，默認創建多少對象
    static const int DEFZULT_SIZE;
};

// 定義靜態常量
template <class T>
const int ObjectPool<T>::DEFZULT_SIZE = 30;

// 靜態變量
template <class T>
ObjectPool<T>* ObjectPool<T>::instance = nullptr;

// 靜態方法
template <class T>
ObjectPool<T>* ObjectPool<T>::getInstance()
{
    if(!instance) instance = new ObjectPool<T>;
    {
        return instance;
    }
}

// 獲取對象
template <class T>
void ObjectPool<T>::allocate()
{
    // 塊
    std::vector<T*>* newObjcetList = new std::vector<T*>(DEFZULT_SIZE);
    
    for(int i = 0; i < DEFZULT_SIZE; i++)
    {
        (*newObjcetList)[i] = T::create();
        (*newObjcetList)[i]->retain();
    }
    // 內存空間的賦值
    mAllObjectList.push_back(newObjcetList);
    
    // 空閒池
    for(int i = 0; i < DEFZULT_SIZE; i++)
    {
        mPoolList.push((*newObjcetList)[i]);
    }
}

// 釋放內存塊
template <class T>
void ObjectPool<T>::disposeObjectArray(std::vector<T*>* objArrary)
{
    for(int i; i < DEFZULT_SIZE; i++)
    {
        T* object = (*objArrary)[i];
        object->release();
    }
    objArrary->clear();
    delete objArrary;
}

// 獲取對象 利用返回模板類型的對象的指針來獲取對象（能夠在對象池中獲得對象的接口
template <class T>
T* ObjectPool<T>::takeout()
{
    // 判斷空閒池是否為空
    if(mPoolList.empty())
    {
        allocate();
    }
    T* obj = mPoolList.front();
    mPoolList.pop();
    return obj;
}

// 回收對象
template <class T>
void ObjectPool<T>::recycle(T* obj)
{
    mPoolList.push(obj);
}

#endif /* ObjectPool_hpp */
