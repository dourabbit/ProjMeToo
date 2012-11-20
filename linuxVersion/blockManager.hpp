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
class BlockManager{
    
public:
    BlockManager(int numOfThread);
    ~BlockManager();
    BlockManager* getManager();
    void Run(void *ptr);
private:
    BlockManager *_singleton;
    int _numOfThread;
    Tracer::PathTracerSplitted* _tracer;
    
};

#endif
