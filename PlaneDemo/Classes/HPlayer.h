//
//  HPlayer.h
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#ifndef __TankDemo__HPlayer__
#define __TankDemo__HPlayer__

#include "cocos2d.h"
#include <sstream>
using namespace std;
using namespace cocos2d;

//主要用于将int float 等数字转换成string类型
template<typename T>
string Convert2String(const T &value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}


class HPlayer : public cocos2d::CCSprite,public CCTouchDelegate
{
public:
    static HPlayer* createPlayer(const char* fileName);//实例函数
    int hp;//血量
    int hpMax;//血量最大值
    int score;//分数
    int killCount;//杀敌数
    void downHp();//掉血
    void addScore(float _value);//加分
    void addKillCount(float _value);//加杀敌数
    bool isDead;//是否死亡
    
private:
    int strongTime;//无敌时间
    bool isStrong;//是否处于无敌时间
    int strongCount;//无敌时的计数器
    void strongIng();//处理无敌时的闪烁等处理
    
    void playerInit();//初始化函数
    
    void storeScore(int _score);
    
    //生命周期相关函数
    virtual void onEnter();
    virtual void onExit();
    
    //触屏事件相关函数
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};
#endif
