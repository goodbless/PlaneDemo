//
//  HAbout.h
//  TankDemo
//
//  Created by Himi on 12-10-21.
//
//

#ifndef __TankDemo__HAbout__
#define __TankDemo__HAbout__


#include "cocos2d.h"

class HAbout : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(HAbout);
    
private:
    //菜单项"返回主菜单"的回调函数
    void backMenu();

};
#endif /* defined(__TankDemo__HAbout__) */
