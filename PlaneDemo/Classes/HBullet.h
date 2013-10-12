//
//  HBullet.h
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#ifndef __TankDemo__HBullet__
#define __TankDemo__HBullet__

#include "cocos2d.h"
using namespace cocos2d;

class HBullet : public cocos2d::CCSprite
{
public:
    //实例化函数
    static HBullet* createBullet(const char* _fileName,float _speed,CCPoint _position);
    void fireFrom(CCPoint _position);
    
private:
    //初始化函数
    void bulletInit(float _speed,CCPoint _position);
    void update(float time);//逻辑
    float speed;//移动速度
    
    virtual void onExit();
};
#endif

