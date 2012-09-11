//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <3rdParty\SDL-1.2.15\SDL.h>
#include <Tracer/pathTracerSplitted.hpp>
#include <Tracer/pathTracer.hpp>
//==============================================================================
class CApp {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;
		Vec* c;
		int w,h;

		Tracer::PathTracerSplitted*		tracer; 

    public:
        CApp();

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
