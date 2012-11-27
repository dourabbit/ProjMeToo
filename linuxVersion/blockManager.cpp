//
//  worker.cpp
//  ___PROJECTNAME___
//
//  Created by Chengfu on 12-11-17.
//
//

#include <blockManager.hpp>
#include <cmath>
#include <sstream>
BlockManager* BlockManager::_singleton=NULL;
Tracer::PathTracerSplitted* BlockManager::_tracer = NULL;
//Block* BlockManager::block = NULL;
int BlockManager::numOfCPUs = 4;
int BlockManager::blockWidth = 50;
int BlockManager::blockHeight =50;

int BlockManager::renderHeight = 0;
int BlockManager::renderWidth = 0;

vector<Block*> BlockManager::blockVecs;
vector<SDL_Thread*> BlockManager::pool;
BlockManager::BlockManager(const int numOfThread,vector<SDL_Thread*> threadP,
                           const int width, const int height){
    pool = threadP;
    renderHeight = width;
    renderWidth = height;
    numOfCPUs = numOfThread;
    _tracer = new Tracer::PathTracerSplitted();
    BlockManager::_singleton = this;
};
BlockManager::~BlockManager(){
    _singleton = NULL;
    delete _tracer;
    
    while (!blockVecs.empty()) {
        delete blockVecs.back();
        blockVecs.pop_back();
    }

    
}
BlockManager* BlockManager::getManager(){
    assert(BlockManager::_singleton!=NULL);
    return _singleton;
};
/*
int BlockManager::Run(void *ptr){

	Block* result = (Block*) ptr;
	Block* block = new Block(Vec2D<int>(0,0),"test",250,25);
	block->Initialize(result);
	_tracer->Render(block);

	delete block;
	return 0;
};
*/
void BlockManager::genBlocks(){
    
    int reminderX = renderWidth % blockWidth;
    int reminderY = renderHeight % blockHeight;
    
    int nx = renderWidth/blockWidth,ny = renderHeight/blockHeight;
    nx += reminderX==0?0:1;
    ny += reminderY==0?0:1;
    
    reminderX = reminderX==0?blockWidth:reminderX;
    reminderY = reminderY==0?blockHeight:reminderY;
    
    for(int iy=0; iy < ny; iy++){
        for(int ix=0; ix < nx; ix++){
            stringstream nstr;
            nstr<< iy*nx + ix;
            string blockNm = "block"+nstr.str();
            if(ix!=nx-1&&iy!=ny-1)//full block
                blockVecs.push_back(new Block(Vec2D<int>(ix*blockWidth,iy*blockHeight),blockNm,blockWidth,blockHeight));
            else if(ix==nx-1&&iy!=ny-1)// last col
                 blockVecs.push_back(new Block(Vec2D<int>(ix*blockWidth,iy*blockHeight),blockNm,reminderX,blockHeight));
            else if(iy==ny-1&&ix!=nx-1)// last row
                blockVecs.push_back(new Block(Vec2D<int>(ix*blockWidth,iy*blockHeight),blockNm,blockWidth,reminderY));
            else//last one
               blockVecs.push_back(new Block(Vec2D<int>(ix*blockWidth,iy*blockHeight),blockNm,reminderX,reminderY));
        }
    }
};
int BlockManager::Run(void* ptr){
    Block* result = (Block*) ptr;
    
    genBlocks();
	//Block* block = new Block(Vec2D<int>(350,100),"test",250,250);
    
    
    //while (!blockVecs.empty()) {
        for(int n=0;n<numOfCPUs;n++){
            Block* block = blockVecs.back();
            block->Initialize(result);
            int threadReturnValue;
            SDL_Thread* thread = SDL_CreateThread(_tracer->Render, (void*)block);
            if( NULL == thread )
                printf("\nError: Creating SDL_Thread failed -> \n", SDL_GetError());
            else
            {
                
                pool.push_back(thread);
                blockVecs.pop_back();
                
                // Wait for the thread to complete. The thread functions return code will
                //       be placed in the "threadReturnValue" variable when it completes.
                //
                SDL_WaitThread( thread, &threadReturnValue);
                pool.pop_back();
                if(!blockVecs.empty()){
                    Block* block = blockVecs.back();
                    block->Initialize(result);
                    SDL_Thread* newThread = SDL_CreateThread(_tracer->Render, (void*)block);
                    pool.push_back(newThread);
                }
            }

        }
//        while (!pool.empty()) {
//            int threadReturnValue;
//            SDL_Thread* thread =  pool.back();
//            SDL_WaitThread(thread, &threadReturnValue);
//            pool.pop_back();
//        }
    //}
    
    
//	for(int i = 0;i<blockVecs.size();i++){
//        for(int n=0;n<numOfCPUs)
//        Block* block =  blockVecs[i];
//        block->Initialize(result);
//        _tracer->Render(block);
//    }
	//delete block;
	return 0;
};