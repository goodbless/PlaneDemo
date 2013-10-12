//
//  HEnemy.h
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#ifndef __TankDemo__HEnemy__
#define __TankDemo__HEnemy__


#include "cocos2d.h"
using namespace cocos2d;

class HEnemy : public cocos2d::CCSprite
{
public:
    //实例化函数
    static HEnemy* createEnemy(const char* fileName,int _type);
    //价值多少分数
    int scoreValue;
private:
    //初始化
    void enemyInit(const char* fileName,int _type);
    
    //敌人成动态表现
    void createAnimate(const char* fileName,int allCount);
    //敌人逻辑
    void update(float time);
    //是否已经运动过了
    bool isActed;
    //当前敌人类型
    int type;
};
#endif