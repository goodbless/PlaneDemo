//
//  World.h
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#ifndef __TankDemo__World__
#define __TankDemo__World__


#include "cocos2d.h"
#include "HPlayer.h"
typedef enum{
    tag_player,//主角
    tag_playerHp1,//血量1
    tag_playerHp2,//血量2
    tag_playerHp3,//血量3
    tag_scoreTTF,//分数
    tag_killsCountTTF,//杀敌数
}tagWorld;//枚举变量

class HWorld : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    //获取当前HWorld的静态实例
    static HWorld * sharedWorld();
    //获取主角
    HPlayer* getPlayer();
    //获取存放敌怪的数组
    CCArray* getArrayForEnemy();
    
    
    int numBullet;
    void winGame();
    void lostGame();
    
private:
    virtual bool init();
    CREATE_FUNC(HWorld);
    
    CCArray * arrayEnemy;//存放敌怪的数组
    CCSpriteBatchNode* bulletSpriteBatch;
    CCArray* bulletArr;
    void autoCreateBullet();//自动创建子弹
    void autoCreateEnemy();//自动创建敌怪
    void backMenu();//返回主菜单
    virtual ~HWorld();//析构函数
};

#endif /* defined(__TankDemo__World__) */
