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

#include <pathTracerSplitted.hpp>
BlockManager* BlockManager::_singleton=NULL;
Tracer::PathTracerSplitted* BlockManager::_tracer = NULL;

//Block* BlockManager::block = NULL;
int BlockManager::numOfCPUs = 4;
int BlockManager::blockWidth = 50;
int BlockManager::blockHeight =50;

int BlockManager::renderHeight = 0;
int BlockManager::renderWidth = 0;

vector<Block*> BlockManager::blockPool;
vector<SDL_Thread*> threadPool;
//vector<ManageInfo*> BlockManager::infoPool;



//vector<Block*> blockPool;
BlockManager::BlockManager(const int numOfThread,vector<SDL_Thread*> threadP,
                           const int width, const int height){
    //threadPool = threadP;
    renderHeight = width;
    renderWidth = height;
    numOfCPUs = numOfThread;
    
	_tracer = new Tracer::PathTracerSplitted();
	_tracer->Initialize();
	_tracer->width = width;
	_tracer->height = height;

    BlockManager::_singleton = this;
};
BlockManager::~BlockManager(){
    
    delete _tracer;

}
void BlockManager::CleanUp(){
    
    
    //_singleton = NULL;
    SDL_mutexP(mutLock);
    EXITFLAG = 1;
	SDL_mutexV(mutLock);
	for(int i=0;i<threadPool.size();i++) {
		SDL_Thread* thread = threadPool[i];
		Uint32 id =  SDL_GetThreadID(thread);
		//delete thread;
		//SDL_KillThread(thread);
		//printf("Killed thread:%d",id);
        threadPool.pop_back();
	}
    SDL_Delay(950);
    while (!blockPool.empty()) {
        //delete blockPool.back();
        blockPool.pop_back();
    }

}
BlockManager* BlockManager::getManager(){
    assert(BlockManager::_singleton!=NULL);
    return _singleton;
};

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
                blockPool.push_back(new Block(Vec2D<int>(ix*blockWidth,iy*blockHeight),blockNm,blockWidth,blockHeight));
            else if(ix==nx-1&&iy!=ny-1)// last col
                 blockPool.push_back(new Block(Vec2D<int>(ix*blockWidth,iy*blockHeight),blockNm,reminderX,blockHeight));
            else if(iy==ny-1&&ix!=nx-1)// last row
                blockPool.push_back(new Block(Vec2D<int>(ix*blockWidth,iy*blockHeight),blockNm,blockWidth,reminderY));
            else//last one
               blockPool.push_back(new Block(Vec2D<int>(ix*blockWidth,iy*blockHeight),blockNm,reminderX,reminderY));
        }
    }
};
int startRendering(void* ptr){
    //ImgWriter* writer = new ImgWriter();
	Tracer::PathTracerSplitted::ManagedRender(&BlockManager::blockPool,&ImgWriter::Write);
	return 0;
};





int BlockManager::Run(void* ptr){
    Block* result = (Block*) ptr;
    mutLock=SDL_CreateMutex();

    genBlocks();


	for (std::vector<Block*>::iterator i = blockPool.begin(); i != blockPool.end(); ++i) { // Iterate through 'items'
		(*i)->Initialize(result);
	}
	for(int n=0;n<numOfCPUs-1;n++){
        int a =0;
		SDL_Thread* thread = SDL_CreateThread(startRendering,(void*)&a);
	}

	return 0;
};