//
//  worker.h
//  ___PROJECTNAME___
//
//  Created by Chengfu on 12-11-17.
//
//

#ifndef _WORKERMANAGER_H_
#define _WORKERMANAGER_H_

#include "pathTracerSplitted.hpp"
#include "worker.hpp"
#include <vector>

#include "common.h"
#include <string>
struct ManageInfo{
	Tracer::PathTracerSplitted* tracer;
	//SDL_Thread* thread;
	vector<Block*> blockPool;
};

class BlockManager{
    
public:
    BlockManager(const int numOfThread,vector<SDL_Thread*> pool, const int width, const int height);
    ~BlockManager();
    void CleanUp();
	//static vector<SDL_Thread*> threadPool;
    static BlockManager* getManager();
    static int renderWidth;
    static int renderHeight;
    static int Run(void* ptr);
    static int numOfCPUs;
    static int blockWidth;
    static int blockHeight;
	static vector<Block*> blockPool;
    
    static void SetRenderPath();
private:
    static std::string _pathNm;
    
    static BlockManager*  _singleton;
    //static ImgWriter* writer;
   
    static Tracer::PathTracerSplitted* _tracer;
    static void genBlocks();
    
};

#endif
