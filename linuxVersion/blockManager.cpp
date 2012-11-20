//
//  worker.cpp
//  ___PROJECTNAME___
//
//  Created by Chengfu on 12-11-17.
//
//

#include <blockManager.hpp>

BlockManager::BlockManager(int numOfThread){
    
    this->_numOfThread = numOfThread;
    this->_tracer = new Tracer::PathTracerSplitted();
    this->_singleton = this;
};
BlockManager* BlockManager::getManager(){
    assert(_singleton!=NULL);
    return this->_singleton;
};
void BlockManager::Run(void *ptr){
    Vec* col = (Vec*) ptr;
    Block* block = new Block(Vec2D<int>(0,0),"test",100,100);
    this->_tracer->Render(*block);
    col = block->wholeBlock->col;
};
