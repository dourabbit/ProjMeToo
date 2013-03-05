//
//  main.cpp
//  MeToo
//
//  Created by Chengfu on 13-3-5.
//  Copyright (c) 2013年 PongStudio. All rights reserved.
//

#include <iostream>
#include "CApp.h"
#include <common.h>
#include <vector>

 const vector<Shape*> Scene::sceneObjs;
 const vector<Light*> Scene::lights;


vector<int*> test;
vector<Shape*>* sceneObjs;
vector<Light*>* lights;

void InitializeScenes(){
    
    int a =2;
    
    sceneObjs = const_cast<vector<Shape*>*>(&Scene::sceneObjs);
    lights = const_cast<vector<Light*>*>(&Scene::lights);
    //Scene::test.push_back(&a);

	
    sceneObjs->push_back(new Sphere("sphere",Vec(-10,4,0),9, Zero,  Vec(.25,.25,.25),DIFF));//Glass
	AreaLight* light = new AreaLight("AreaLight",Vec(0,30,10),Vec(180,0,0),10,10,Vec(120,120,120));
	sceneObjs->push_back(light);//Light
	sceneObjs->push_back(new Plane("right",	Vec(40,0,0),	Vec(0,0,90),	80,80,		Zero,Vec(.75,.25,.25),DIFF));//Right
	sceneObjs->push_back(new Plane("left",	Vec(-40,0,0),	Vec(0,0,-90),	80,80,		Zero,Vec(.25,.25,.75),DIFF));//Left
	sceneObjs->push_back(new Plane("top",	Vec(0,40,0),	Vec(0,0,-180),	80,80,		Zero,Vec(.25,.25,.25),DIFF));//Top
	sceneObjs->push_back(new Plane("bottom",	Vec(0,-40,0),	Vec(0,0,0),		80,80,		Zero,Vec(.25,.25,.25),DIFF));//Bottom
	sceneObjs->push_back(new Plane("back",	Vec(0,0,-40),	Vec(90,0,0),	80,80,		Zero,Vec(.25,.25,.25),DIFF));//Back
	sceneObjs->push_back(new Plane("back",	Vec(0,0,60),	Vec(-90,0,0),	80,80,		Zero,Vec(.25,.25,.25),DIFF));//Back
    
    for (int i = 0; i<Scene::sceneObjs.size(); i++) {
		Light* light=NULL;
		light = dynamic_cast<Light*>(Scene::sceneObjs[i]);
        
		if(light)
			lights->push_back(light);
	}
    //    AreaLight* light = new AreaLight("AreaLight",Vec(0,30,10),Vec(180,0,0),10,10,Vec(120,120,120));
    //    scene.sceneObjs= (Shape**)malloc(sizeof(Shape**)*8);
    //    scene.sceneObjs[0]=new Sphere("sphere",Vec(-10,4,0),9, Zero,  Vec(.25,.25,.25),DIFF);
    //    scene.sceneObjs[1]=light;
    
    
};


int main(int argc, const char * argv[])
{
    
    InitializeScenes();
    CApp app;
    app.OnInit();
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

