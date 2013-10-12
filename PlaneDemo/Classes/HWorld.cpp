//
//  HWorld.cpp
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#include "HWorld.h"
#include "HMap.h"
#include "HBullet.h"
#include "HEnemy.h"
#include "HMenu.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

static HWorld * sh;

HWorld * HWorld::sharedWorld(){
    if(sh!=NULL){
        return sh;
    }
    return NULL;
}

CCScene* HWorld::scene()
{
    CCScene *scene = CCScene::create();
    HWorld *layer = HWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    sh=this;
    
    //播放游戏中的音乐
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameMusic.mp3",true);
    
    //初始化敌人数组
    arrayEnemy= CCArray::create();
    CC_SAFE_RETAIN(arrayEnemy);
    
    //地图
    HMap * map  = HMap::createMap("map.png");
    addChild(map);
    
    //主角
    HPlayer * player=HPlayer::createPlayer("player.png");
    addChild(player,0,tag_player);
    
    bulletSpriteBatch = CCSpriteBatchNode::create("p_bullet.png");
    addChild(bulletSpriteBatch);
    
    bulletArr = CCArray::create();
    bulletArr->retain();
    
    numBullet = 0;
    
    for (int i = 0; i < 100; i++) {
        HBullet* bullet = HBullet::createBullet("p_bullet.png", 8, ccp(-100,-100));
        bullet->setVisible(false);
        bulletSpriteBatch->addChild(bullet);
        bulletArr->addObject(bullet);
        
    }
    
    //创建子弹逻辑（创建间隔0.37秒）
    this->schedule(schedule_selector(HWorld::autoCreateBullet),0.1);
    //创建敌怪逻辑（创建间隔1秒）
    this->schedule(schedule_selector(HWorld::autoCreateEnemy),1);
    return true;
}

//自动创建敌怪对象
void HWorld::autoCreateEnemy(){
    int randomCount=CCRANDOM_0_1()*10;//随机本次创建enemy的个数
    for (int i =0; i<randomCount; i++) {
        int random=CCRANDOM_0_1()*10;
        HEnemy* enemy=NULL;
        int randomType = CCRANDOM_0_1()*10;
        
        //随机怪的贴图
        const char* name;
        if(random>=0 && random<=2){
            name="enemy_bug.png";
        }else if(random>=3 && random<=6){
            name="enemy_duck.png";
        }else if(random>=7 && random<=10){
            name="enemy_pig.png";
        }
        //随机类型
        if(randomType%2 ==0){
            randomType=0;
        }else{
            randomType=1;
        }
        enemy=HEnemy::createEnemy(name, randomType);
        arrayEnemy->addObject(enemy);
        addChild(enemy);
    }
}

//自动添加子弹
void HWorld::autoCreateBullet(){
    //主角子弹
     HPlayer * player = (HPlayer*)this->getChildByTag(tag_player);
    HBullet * bullet = (HBullet*)bulletArr->objectAtIndex(numBullet);
    numBullet++;
    if (numBullet >= bulletArr->count()) {
        numBullet = 0;
    }
    bullet->fireFrom(ccpAdd(player->getPosition(), ccp(0,player->getContentSize().height*0.5)));
//    this->addChild(HBullet::createBullet("p_bullet.png",8,ccpAdd(player->getPosition(), ccp(0,player->getContentSize().height*0.5))));

    //子弹音效
    SimpleAudioEngine::sharedEngine()->playEffect("effect_bullet.mp3");
}

//游戏胜利
void HWorld::winGame(){
    
    //添加胜利界面
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 190), size.width, size.height);
    CCSprite* sp = CCSprite::create("game_win.png");
    sp->setPosition(ccp(size.width*0.5,size.height*0.5));
    layer->addChild(sp);
    addChild(layer,100);
    
    //添加一个按钮用于返回Menu
    CCLabelTTF* ttback =CCLabelTTF::create("返回主菜单", "Helvetica-Bold", 23);
    CCMenuItemLabel* menuLabel= CCMenuItemLabel::create(ttback, this, menu_selector(HWorld::backMenu));
    menuLabel->setPosition(ccp(0,-200));
    CCMenu* menu =CCMenu::create(menuLabel,NULL);
    addChild(menu,100);
    
    
    //暂停游戏
    CCDirector::sharedDirector()->pause();
}
//游戏失败
void HWorld::lostGame(){
    //添加失败界面
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 255), size.width, size.height);
    CCSprite* sp = CCSprite::create("game_lost.png");
    sp->setPosition(ccp(size.width*0.5,size.height*0.5));
    layer->addChild(sp);
    addChild(layer,100);
    
    //添加一个按钮用于返回Menu
    CCLabelTTF* ttback =CCLabelTTF::create("返回主菜单", "Helvetica-Bold", 23);
    CCMenuItemLabel* menuLabel= CCMenuItemLabel::create(ttback, this, menu_selector(HWorld::backMenu));
    menuLabel->setPosition(ccp(0,-200));
    CCMenu* menu =CCMenu::create(menuLabel,NULL);
    addChild(menu,100);
    
    //暂停游戏
    CCDirector::sharedDirector()->pause();
}

//菜单项"返回主菜单"的回调函数
void HWorld::backMenu(){
    this->unscheduleAllSelectors();
    //继续游戏
    CCDirector::sharedDirector()->resume();
    //切换到"菜单"场景
    CCDirector::sharedDirector()->replaceScene(HMenu::scene());
}

//获取主角
HPlayer* HWorld::getPlayer(){
    HPlayer* player = (HPlayer*)HWorld::sharedWorld()->getChildByTag(tag_player);
    return player;
}

//获取敌人数组
CCArray* HWorld::getArrayForEnemy(){
    return arrayEnemy;
}

HWorld::~HWorld(){
    CC_SAFE_RELEASE(bulletArr);
    CC_SAFE_RELEASE(arrayEnemy);
}


























































