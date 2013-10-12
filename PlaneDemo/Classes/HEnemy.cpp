//
//  HEnemy.cpp
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#include "HEnemy.h"
#include "HWorld.h"

HEnemy* HEnemy::createEnemy(const char* fileName,int _type){
    HEnemy* enemy = new HEnemy();
    if(enemy && enemy->initWithFile(fileName)){
        enemy->autorelease();
        enemy->enemyInit(fileName,_type);
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}
//初始化
void HEnemy::enemyInit(const char* fileName,int _type){
    type=_type;
    createAnimate(fileName, 10);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if(_type==0){
        scoreValue=198;
    }else if(_type==1){
        scoreValue=428;
    }else if(_type ==2){
        scoreValue=908;
    }
    //X在屏幕内随机位置
    this->setPosition(ccp(CCRANDOM_0_1()*size.width,size.height+this->getContentSize().height));
    //敌人逻辑
    this->scheduleUpdate();
}
//三种不同的移动逻辑
void HEnemy::update(float time){
    switch (type) {
        case 0:{
            this->setPosition(ccpAdd(this->getPosition(), ccp(0,-3)));
            break;
        }
        case 1:{
            //判断防止重复调用此动作，保证此逻辑只会执行一次
            if(isActed){
                break;
            }
            isActed=true;
            this->runAction( CCSequence::create(CCMoveTo::create(1.6, HWorld::sharedWorld()->getPlayer()->getPosition()),
                                                CCDelayTime::create(0.5),
                                                CCMoveTo::create(0.8, this->getPosition()),NULL));
            break;
        }
        case 2:
        {
            if(isActed){
                break;
            }
            isActed=true;
            this->runAction( CCSequence::create(CCMoveTo::create(1.6, HWorld::sharedWorld()->getPlayer()->getPosition()),
                                                CCDelayTime::create(1),
                                                CCMoveTo::create(0.8, this->getPosition()),NULL));
        }
            break;
    }
    //删除
    if(this->getPositionY()<-this->getContentSize().height){
        //
        HWorld::sharedWorld()->getArrayForEnemy()->removeObject(this);
        //从父类删除当前敌怪
        this->getParent()->removeChild(this, true);
    }

    HPlayer * player = HWorld::sharedWorld()->getPlayer();
    if(!player->isDead){
        if(player->boundingBox().intersectsRect(this->boundingBox())){
            player->downHp();
        }
    }
    
}

//让敌怪有动态的效果
void HEnemy::createAnimate(const char* fileName,int allCount){

    CCAnimation* animation = CCAnimation::create();
    CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(fileName);
    int eachWidth=this->getContentSize().width/allCount;//每个切片的宽
    for (int i =0; i<allCount; i++) {
        animation->addSpriteFrameWithTexture(texture,CCRectMake(i*eachWidth, 0, eachWidth, this->getContentSize().height));
    }
    animation->setDelayPerUnit(0.03f);//必须设置否则不会动态播放
    animation->setRestoreOriginalFrame(true);//是否回到第一帧
    animation->setLoops(-1);//重复次数 （-1:无限循环）
    CCFiniteTimeAction * animate = CCAnimate::create(animation);
    this->runAction(animate);
}