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
// These includes are necessary to get the plug-in compile !
//#include <cstdio>
//#include <jpeglib.h>
//#include <jerror.h>
//#define cimg_plugin "plugins/jpeg_buffer.h"
//#include <CImg.h>
using namespace std;

class Block{
private:
public:
    
    unsigned char* _buffer;
    static Block* wholeBlock;
    Vec2D<int>   pos;
    
    Vec*   col;
    //CImg<unsigned char> img;
    
    int width;
    int height;
    string blockNm;
    

    Block();
    Block(const Vec2D<int> &p,const string &name, const int &w, const int &h){        
            col = new Vec[w*h];
			pos = p;
			blockNm = name;
			width = w;
			height = h;
            //memset(_buffer,0,w*h*3*sizeof(unsigned char));
            _buffer = new unsigned char[w*h*3];
            memset(_buffer,0,w*h*3*sizeof(unsigned char));
            //img(_buffer,w,h,1,3,true);
			//if(this->wholeBlock==NULL) this->wholeBlock = this;
    };
    ~Block(){
        delete[] _buffer;
        delete col;
    };
	void Initialize(Block* result){
            
        this->wholeBlock = result;
        
//		this->wholeBlock = new  Block(Vec2D<int>(0,0),"test",width,height);
//		for(int i=0;i<width*height;i++){
//			this->wholeBlock->col[i].x = this->wholeBlock->col[i].y = this->wholeBlock->col[i].z = 0;
//			
//			//this->wholeBlock->col
//		}
	};
    
    void Cp2Buffer() const{
//        for(int x = 0; x<this->width; x++){
//            for(int y = 0; y<this->height; y++){
//                this->col[x*y+x];
//            }
//        }
        
        const int d = width*height;
        for(int i=0;i<width*height;i++){
            *(_buffer+i) = this->col[i].x*255;
            *(_buffer+i+d) = this->col[i].y*255;
            *(_buffer+i+2*d) = this->col[i].z*255;
        }
    }
    
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
        localIndex = ((globalIndex/this->wholeBlock->height)-this->pos.y)*this->width+
        ((globalIndex%this->wholeBlock->height)-this->pos.x);
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
