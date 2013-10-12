//
//  HMenu.h
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#ifndef __TankDemo__HMenu__
#define __TankDemo__HMenu__

#include "cocos2d.h"

class HMenu : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(HMenu);

private:
    //当点击"Play"菜单项触发的回调函数
    void playIsPressed();
    //当点击"Score"菜单项触发的回调函数
    void scoreIsPressed();
    //当点击"About"菜单项触发的回调函数
    void aboutIsPressed();
    
};
#endif /* defined(__TankDemo__HMenu__) */
