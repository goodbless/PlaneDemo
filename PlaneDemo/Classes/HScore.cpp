//
//  HScore.cpp
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#include "HScore.h"
#include "HMenu.h"
using namespace cocos2d;

CCScene* HScore::scene()
{
    CCScene *scene = CCScene::create();
    HScore *layer = HScore::create();
    scene->addChild(layer);
    return scene;
}

bool HScore::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //获取设置尺寸
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //背景
    CCSprite* sp = CCSprite::create("score_bg.png");
    sp->setPosition(ccp(size.width*0.5,size.height*0.5));
    addChild(sp);
    
    //添加一个文本(获取存储的积分)
    std::string scoreStr="";
    //获取存储的积分
    std::string score =CCUserDefault::sharedUserDefault()->getStringForKey("user_score","-1").c_str();
    //判断当前是否有最高分的记录
    if(atoi(score.c_str())!=-1){
        //如有有最高分的记录
        scoreStr+=score;
    }else{
        scoreStr="0";
    }
    //将分数以Lable添加到layer并显示出来
    CCLabelTTF* ttfAbout = CCLabelTTF::create(scoreStr.c_str(), "Helvetica", 23);
    ttfAbout->setPosition(ccp(size.width*0.5-50,size.height*0.5+40));
    ttfAbout->setColor(ccc3(255, 0, 0));
    addChild(ttfAbout);
    
    //添加一个按钮用于返回Menu
    CCLabelTTF* ttback =CCLabelTTF::create("返回主菜单", "Helvetica", 23);
    ttback->setColor(ccc3(255, 255, 0));
    CCMenuItemLabel* menuLabel= CCMenuItemLabel::create(ttback, this, menu_selector(HScore::backMenu));
    menuLabel->setPosition(ccp(0,-200));
    CCMenu* menu =CCMenu::create(menuLabel,NULL);
    addChild(menu);
    
    return true;
}
void HScore::backMenu(){
    //切换到"菜单"场景
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.5, HMenu::scene()));
}

