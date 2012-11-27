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
#include <SDL.h>
#include <vector>
class BlockManager{
    
public:
    BlockManager(const int numOfThread,vector<SDL_Thread*> pool, const int width, const int height);
    ~BlockManager();
    static vector<SDL_Thread*> pool;
    static BlockManager* getManager();
    static int renderWidth;
    static int renderHeight;
    static int Run(void* ptr);
    static int numOfCPUs;
    static int blockWidth;
    static int blockHeight;
	//static int Run(Block *block);
private:
    static BlockManager*  _singleton;
    static vector<Block*> blockVecs;
    static Tracer::PathTracerSplitted* _tracer;
    static void genBlocks();
    
};

#endif
