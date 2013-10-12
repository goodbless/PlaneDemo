//
//  HMenu.cpp
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#include "HMenu.h"
#include "HWorld.h"
#include "HAbout.h"
#include "HScore.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

CCScene* HMenu::scene()
{
    CCScene *scene = CCScene::create();
    HMenu *layer = HMenu::create();
    scene->addChild(layer);
    return scene;
}

bool HMenu::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    //播放菜单场景的音乐
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menuMusic.mp3",true);
    
    //获取整个设备的尺寸
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //创建Menu背景
    CCSprite* sp = CCSprite::create("menu_bg.png");
    sp->setPosition(ccp(size.width*0.5,size.height*0.5));
    addChild(sp);
    
    //创建Menu菜单项-play
    CCMenuItemImage * itemPlay= CCMenuItemImage::create("play_nor.png", "play_pre.png",this,menu_selector(HMenu::playIsPressed));
    
    //创建Menu菜单项-score
    CCMenuItemImage * itemScore= CCMenuItemImage::create("score_nor.png", "score_pre.png",this,menu_selector(HMenu::scoreIsPressed));
    itemScore->setPosition(ccp(0,-itemScore->getContentSize().height-20));
    
    //创建Menu菜单项-about
    CCMenuItemImage * itemAbout= CCMenuItemImage::create("about_nor.png", "about_pre.png",this,menu_selector(HMenu::aboutIsPressed));
    itemAbout->setPosition(ccp(0,-itemScore->getContentSize().height*2-40));
    
    //利用3个菜单项创建Menu菜单
    CCMenu * menu = CCMenu::create(itemPlay,itemScore,itemAbout,NULL);
    addChild(menu);
    
    return true;
}
//菜单项Play被按下时的回调函数
void HMenu::playIsPressed(){
    //切换到"游戏"场景
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5, HWorld::scene()));
}

//菜单项High Scores被按下时的回调函数
void HMenu::scoreIsPressed(){
    //切换到“高分”场景
    CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.5, HScore::scene()));
}

//菜单项About被按下时的回调函数
void HMenu::aboutIsPressed(){
    //切换到“关于”场景
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(1.5, HAbout::scene()));
}

