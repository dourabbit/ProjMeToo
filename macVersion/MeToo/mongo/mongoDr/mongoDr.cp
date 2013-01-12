/*
 *  mongoDr.cp
 *  mongoDr
 *
 *  Created by Chengfu on 13-1-12.
 *  Copyright (c) 2013年 PongStudio. All rights reserved.
 *
 */

#include <iostream>
#include "mongoDr.h"
#include "mongoDrPriv.h"

void mongoDr::HelloWorld(const char * s)
{
	 mongoDrPriv *theObj = new mongoDrPriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void mongoDrPriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

