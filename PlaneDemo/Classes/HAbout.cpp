//
//  HAbout.cpp
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#include "HAbout.h"
#include "HMenu.h"
using namespace cocos2d;

CCScene* HAbout::scene()
{
    CCScene *scene = CCScene::create();
    HAbout *layer = HAbout::create();
    scene->addChild(layer);
    return scene;
}

bool HAbout::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    //获取设备尺寸
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //背景
    CCSprite* sp = CCSprite::create("about_bg.png");
    sp->setPosition(ccp(size.width*0.5,size.height*0.5));
    addChild(sp);
    
    //添加一个按钮用于切换至Menu菜单场景
    CCLabelTTF* ttback =CCLabelTTF::create("返回主菜单", "Helvetica-Bold", 23);
    ttback->setColor(ccc3(255, 255, 0));
    CCMenuItemLabel* menuLabel= CCMenuItemLabel::create(ttback, this, menu_selector(HAbout::backMenu));
    menuLabel->setPosition(ccp(0,-200));
    
    //利用一个菜单项创建一个CCMenu
    CCMenu* menu =CCMenu::create(menuLabel,NULL);
    addChild(menu);
    return true;
}

void HAbout::backMenu(){
    //切换到"菜单"场景
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.5, HMenu::scene(),true));
}
