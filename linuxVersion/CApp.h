//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include "pathTracerSplitted.hpp"
#include <worker.hpp>
#include <vector>
#include "blockManager.hpp"
//==============================================================================
class CApp {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;
		//Vec* c;
		Block* wholeBlock;
		int w,h;
        Block* result;
		BlockManager* manager;
		Tracer::PathTracerSplitted*		tracer;

		vector<SDL_Thread*> threadsPool;

    public:
        CApp();
		~CApp();
        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

//==============================================================================

#endif
