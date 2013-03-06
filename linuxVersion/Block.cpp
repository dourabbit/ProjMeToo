//
//  Block.cpp
//  MeToo
//
//  Created by Chengfu on 13-3-6.
//  Copyright (c) 2013年 PongStudio. All rights reserved.
//

#include "Block.hpp"
#pragma once
#include <Math.hpp>
#include <string>
#include <assert.h>


//int * Block::OnFinCB(<#const Block *#>);

Block::Block(const Vec2D<int> &p,const std::string &name, const int &w, const int &h){
        col = new Vec[w*h];
        pos = p;
        blockNm = name;
        width = w;
        height = h;
        //OnFinCB=NULL;
        buff4ImgWriter = new unsigned char[w*h*3];
        memset(buff4ImgWriter,0,w*h*3*sizeof(unsigned char));
};

Block::~Block(){
        delete[] buff4ImgWriter;
        delete col;
};
void Block::Initialize(Block* result){
        
        this->wholeBlock = result;
        
        //		this->wholeBlock = new  Block(Vec2D<int>(0,0),"test",width,height);
        //		for(int i=0;i<width*height;i++){
        //			this->wholeBlock->col[i].x = this->wholeBlock->col[i].y = this->wholeBlock->col[i].z = 0;
        //
        //			//this->wholeBlock->col
        //		}
};
    
void Block::Cp2Buffer() const{
        //        for(int x = 0; x<this->width; x++){
        //            for(int y = 0; y<this->height; y++){
        //                this->col[x*y+x];
        //            }
        //        }
        
        const int d = width*height;
        for(int i=0;i<width*height;i++){
            *(buff4ImgWriter+i) = this->col[i].x*255;
            *(buff4ImgWriter+i+d) = this->col[i].y*255;
            *(buff4ImgWriter+i+2*d) = this->col[i].z*255;
        }
}
    
void Block::CpyBlockBuff() const{
        
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
    
int Block::LocalIndex2Global(const int localIndex) const{
        int globalIndex = -1;
        int row = localIndex/this->width + this->pos.y,
        col = localIndex%this->width + this->pos.x;
        
        return globalIndex = row* wholeBlock->width + col;
};
    
int Block::GlobalIndex2Local(const int globalIndex) const{
        int localIndex = -1;
        localIndex = ((globalIndex/this->wholeBlock->height)-this->pos.y)*this->width+
        ((globalIndex%this->wholeBlock->height)-this->pos.x);
        return localIndex;
        
};
    
Vec2D<int> Block::LocalIndex2Global(const Vec2D<int> localIndex) const{
        Vec2D<int> globalIndex = Vec2D<int>(-1,-1);
        globalIndex.x = localIndex.x + this->pos.x;
        globalIndex.y = localIndex.y + this->pos.y;
        return globalIndex;
};
    