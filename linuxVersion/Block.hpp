#pragma once
#include <Math.hpp>
#include <string>
#include <assert.h>

class Block{
private:
public:
    
    Vec2D<int>   pos;
    std::string blockNm;
    
    unsigned char* buff4ImgWriter;
    static Block* wholeBlock;

    Vec*   col;
    int width;
    int height;
    static int (*OnFinCB) (const Block*);
  
    Block(const Vec2D<int> &p,const std::string &name, const int &w, const int &h);
    
    ~Block();
    
    
    void Initialize(Block* result);
    void Cp2Buffer() const;
    
    void CpyBlockBuff() const;
    int LocalIndex2Global(const int localIndex) const;
    int GlobalIndex2Local(const int globalIndex) const;
    Vec2D<int> LocalIndex2Global(const Vec2D<int> localIndex) const;
};