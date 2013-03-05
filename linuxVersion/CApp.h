
#ifndef _CAPP_H_
    #define _CAPP_H_

#include "pathTracerSplitted.hpp"
#include <worker.hpp>
#include <vector>
#include "blockManager.hpp"
//==============================================================================
class CApp {
    private:
        Block* wholeBlock;
		int w,h;
        Block* result;
		BlockManager* manager;
		Tracer::PathTracerSplitted*		tracer;

		vector<void*> threadsPool;

    public:
        CApp();
		~CApp();
        int OnExecute();

    public:
        bool OnInit();
        
        void OnCleanup();
        void OnRender();
};

//==============================================================================

#endif
