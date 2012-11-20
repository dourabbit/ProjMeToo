//
//  worker.h
//  ___PROJECTNAME___
//
//  Created by Chengfu on 12-11-17.
//
//

#ifndef _WORKER_H_
#define _WORKER_H_
#include <Math.hpp>
#include <iostream>
#include <assert.h>

using namespace std;
class Block{
public:
    
    static Block* wholeBlock;
    Vec2D<int>   pos;
    Vec*   col;
    const int width;
    const int height;
    string blockNm;
    
//    static int totalWidth;
//    static int totalHeight;
//    static Vec* totalCol;

    Block();
    Block(const Vec2D<int> &p,const string &name, const int &w, const int &h):
        pos(p),blockNm(name),width(w),height(h){
        
            col = new Vec[width*height];
        
    };
    ~Block(){
        
        delete col;
    };
    
    
    
    void CpyBlockBuff() const{
        
        assert(wholeBlock!=NULL);
        
       	// Loop over block buffer rows
        int localIndex = 0;
        for (unsigned short y = this->pos.y; y < this->height; y++) {
            // Loop cols
            for (unsigned short x=this->pos.x; x< this->width; x++) {
                const int index = this->height * this->width + x;
                localIndex++;
                
                wholeBlock->col[index] = Vec(col[localIndex].x,this->col[localIndex].y,this->col[localIndex].z);
                
            }
        }
    };
    
    int LocalIndex2Global(const int localIndex) const{
        int globalIndex = -1;
        int row = localIndex/this->width + this->pos.y,
            col = localIndex%this->width + this->pos.x;
        
        return globalIndex = row* wholeBlock->width + col;
    };
    
    int GlobalIndex2Local(const int globalIndex) const{
        int localIndex = -1;
        
        return localIndex;
    
    };
    
    Vec2D<int> LocalIndex2Global(const Vec2D<int> localIndex) const{
        Vec2D<int> globalIndex = Vec2D<int>(-1,-1);
        globalIndex.x = localIndex.x + this->pos.x;
        globalIndex.y = localIndex.y + this->pos.y;
        return globalIndex;
    };
    
};

class Worker:Block{
public:
    Worker();
    ~Worker();
    
    
};


#endif
