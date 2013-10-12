//
//  HBullet.cpp
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#include "HBullet.h"
#include "HWorld.h"
#include "HEnemy.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

HBullet* HBullet::createBullet(const char* _fileName,float _speed,CCPoint _position){
    HBullet* bullet = new HBullet();
    if(bullet && bullet->initWithFile(_fileName)){
        bullet->autorelease();
        bullet->bulletInit(_speed,_position);
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return NULL;
}
void HBullet::bulletInit(float _speed,CCPoint _position){
    speed = _speed;
    this->setPosition(_position);
//    this->scheduleUpdate();
}

void HBullet::fireFrom(cocos2d::CCPoint _position){
    this->setVisible(true);
    this->setPosition(_position);
    this->scheduleUpdate();
    }

//子弹逻辑
void HBullet::update(float time){
    //子弹向上运动
    this->setPosition(ccpAdd(this->getPosition(), ccp(0,speed)));
    if (this->getPosition().y > CCDirector::sharedDirector()->getWinSize().height + this->getContentSize().height*0.5) {
        this->setVisible(false);
        this->setPosition(ccp(-100, -100));
        this->unscheduleUpdate();
    }
    CCArray * array = HWorld::sharedWorld()->getArrayForEnemy();
    for (int i =0; i<array->count(); i++) {
        HEnemy* enemy = (HEnemy*)array->objectAtIndex(i);
        if(enemy->boundingBox().intersectsRect(this->boundingBox())){
            //爆炸音效
            SimpleAudioEngine::sharedEngine()->playEffect("effect_boom.mp3");
            
            //爆炸粒子效果
            CCParticleSystemQuad * particle = CCParticleSystemQuad::create("particle_boom.plist");
            particle->setPosition(enemy->getPosition());//怪的位置
            particle->setAutoRemoveOnFinish(true);//自动释放
            HWorld::sharedWorld()->addChild(particle);//添加到主layer
            
            //增加分数
            HWorld::sharedWorld()->getPlayer()->addScore(enemy->scoreValue);
            
            //添加杀人数
            HWorld::sharedWorld()->getPlayer()->addKillCount(1);
            
            //从敌人数组将被攻击的敌怪删除
            array->removeObject(enemy);
            //删除子弹与敌怪
            HWorld::sharedWorld()->removeChild(enemy, true);
//            HWorld::sharedWorld()->removeChild(this, true);
            this->setVisible(false);
            this->setPosition(ccp(-100, -100));
            this->unscheduleUpdate();
        }
    }
}
//生命周期-退出
void HBullet::onExit(){
    //取消更新函数
    this->unscheduleUpdate();
    CCSprite::onExit();
}