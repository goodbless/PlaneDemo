//
//  HPlayer.cpp
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#include "HPlayer.h"
#include "HBullet.h"
#include "HWorld.h"
using namespace cocos2d;


HPlayer* HPlayer::createPlayer(const char* fileName){
    HPlayer* player = new HPlayer();
    if(player && player->initWithFile(fileName)){
        player->autorelease();
        player->playerInit();
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}

void HPlayer::playerInit(){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    //初始化主角位置
    this->setPosition(ccp(size.width*0.5,this->getContentSize().height*0.5));
    
    hpMax =3;//初始化血量上限为3
    hp=3;//初始化当前血量为3
    score=0;//初始化当前积分分数
    strongTime=2*60;//初始化无敌时间2秒
    
    //初始化3个血,加入到Layer中
    for (int i =0; i<3; i++) {
        CCSprite* spHp = CCSprite::create("icon_hp.png");
        spHp->setPosition(ccp(size.width-this->getContentSize().width*0.5*i-20,spHp->getContentSize().height*0.5));
        if(i==0){
            spHp->setTag(tag_playerHp1);
        }else if(i==1){
            spHp->setTag(tag_playerHp2);
        }else if(i==2){
            spHp->setTag(tag_playerHp3);
        }
        HWorld::sharedWorld()->addChild(spHp,10);
    }
    //初始化"分数"文字加入layer中
    CCLabelTTF* label = CCLabelTTF::create("分数:", "Helvetica-Blod", 24);
    label->setPosition(ccp(30,size.height-22));
    HWorld::sharedWorld()->addChild(label,10);
    
    //分数数字加入layer中
    std::string strScore=Convert2String(score);
    CCLabelTTF* labelScores = CCLabelTTF::create(strScore.c_str(), "Helvetica-Blod", 24);
    labelScores->setPosition(ccp(110,size.height-22));
    labelScores->setColor(ccc3(255, 255, 0));
    HWorld::sharedWorld()->addChild(labelScores,10,tag_scoreTTF);
        
    //杀敌人数
    CCLabelTTF* labelKill = CCLabelTTF::create("杀敌:", "Helvetica-Blod", 24);
    labelKill->setPosition(ccp(30,size.height-52));
    HWorld::sharedWorld()->addChild(labelKill,10);
    
    //杀敌数字加入layer中
    std::string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    CCLabelTTF* labelKillCount = CCLabelTTF::create(strKillCount.c_str(), "Helvetica-Blod", 24);
    labelKillCount->setPosition(ccp(110,size.height-52));
    labelKillCount->setColor(ccc3(255, 255, 0));
    HWorld::sharedWorld()->addChild(labelKillCount,10,tag_killsCountTTF);
}

//添加积分分数
void HPlayer::addScore(float _value){
    score+=_value;
    std::string strScore=Convert2String(score);
    CCLabelTTF* ttf = (CCLabelTTF*)HWorld::sharedWorld()->getChildByTag(tag_scoreTTF);
    ttf->setString(strScore.c_str());
}

//添加杀敌数
void HPlayer::addKillCount(float _value){
    killCount+=_value;
    std::string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    CCLabelTTF* ttf = (CCLabelTTF*)HWorld::sharedWorld()->getChildByTag(tag_killsCountTTF);
    ttf->setString(strKillCount.c_str());
    if(killCount>=100){
        
        //存储分数
//        int oldScore =atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_score","-1").c_str());
//        if(score>oldScore){
//            CCUserDefault::sharedUserDefault()->setStringForKey("user_score", Convert2String(score));
//            CCUserDefault::sharedUserDefault()->flush();
//        }
        storeScore(score);
        
        //调用胜利界面
        HWorld::sharedWorld()->winGame();
    }
}

//主角掉血函数（默认每次掉一点血）
void HPlayer::downHp(){
    if(isStrong){
        return;
    }
    hp-=1;
    if(hp<=0){
        this->setVisible(false);
        isDead=true;
        
        //存储分数
//        int oldScore =atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_score","-1").c_str());
//        if(score>oldScore){
//            CCUserDefault::sharedUserDefault()->setStringForKey("user_score", Convert2String(score));
//            CCUserDefault::sharedUserDefault()->flush();
//        }
        storeScore(score);
        //调用失败界面
        HWorld::sharedWorld()->lostGame();
        
        //调用失败layer
    }else{
        //将界面的血量icon数量进行更新
        switch (hp) {
            case 1:
                HWorld::sharedWorld()->removeChildByTag(tag_playerHp2, true);
                break;
                
            case 2:
                HWorld::sharedWorld()->removeChildByTag(tag_playerHp3, true);
                break;
        }
        //主角无敌时间
        isStrong=true;
        strongCount=0;
        this->schedule(schedule_selector(HPlayer::strongIng));
    }
}

void HPlayer::storeScore(int _score){
    int oldScore =atoi(CCUserDefault::sharedUserDefault()->getStringForKey("user_score","-1").c_str());
    if(_score>oldScore){
        CCUserDefault::sharedUserDefault()->setStringForKey("user_score", Convert2String(_score));
        CCUserDefault::sharedUserDefault()->flush();
    }

}

//处于无敌时间时的处理函数
void HPlayer::strongIng(){
    strongCount++;
    if(strongCount%strongTime ==0){
        this->setVisible(true);
        isStrong=false;
        this->unschedule(schedule_selector(HPlayer::strongIng));
    }else{
        //主角处于无敌时间时的闪烁效果
        if(strongCount%3==0){
            this->setVisible(false);
        }else{
            this->setVisible(true);
        }
    }
}

//进入时注册触屏事件监听
void HPlayer::onEnter(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}


//退出时删除触屏事件监听
void HPlayer::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

//不论哪种触屏事件，都让主角随着用户触屏位置移动
bool HPlayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    this->setPosition(pTouch->getLocation());
    return true;
}

void HPlayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    this->setPosition(pTouch->getLocation());
}

void HPlayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    this->setPosition(pTouch->getLocation());
}