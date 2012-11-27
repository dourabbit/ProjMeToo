
/* Simple program:  Create a blank window, wait for keypress, quit.

   Please see the SDL documentation for details on using the SDL API:
   /Developer/Documentation/SDL/docs.html
*/
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SDL.h"

//==============================================================================
#include <SDLApp/CApp.h>
#include <SDLApp/SDLHelper.hpp>
#include <Tracer/pathTracerSplitted.hpp>
//#include <Tracer/pathTracer.hpp>
#include "Tracer/pathTracerSplitted.hpp"
//#include <Test.h>


int main(int argc, char* argv[]) {
    CApp theApp;
    return theApp.OnExecute();
//    Vec* c = new Vec[100*100];
//    
//    Tracer::PathTracerSplitted* tracer = new Tracer::PathTracerSplitted();
//    tracer->Render(c);
//    return 0;
}

////==============================================================================
//CApp::CApp() {
//    Surf_Display = NULL;
//    Running = true;
//    
//    Test::CodingTest *test;
//    test = new Test::CodingTest::CodingTest();
//	
//
//	tracer = new Tracer::PathTracerSplitted();
//	//tracer->Initialize();
//}
////==============================================================================
//bool CApp::OnInit() {
//    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
//        return false;
//    }
//	w = h= 512;
//    if((Surf_Display = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
//        return false;
//    }
//    
//	SDL_FillRect(Surf_Display, NULL, 0);
//	SDL_Flip(Surf_Display);
//    
//	//SDL_Thread *thread;
//
//	c = new Vec[w * h];
//	//tracer->width  = w;
//	//tracer->height = h;
//	//thread = SDL_CreateThread(tracer->Render,  (void *)c);
//    
//    return true;
//}
////==============================================================================
//
//void CApp::OnLoop() {
//}
////==============================================================================
//
//void CApp::OnRender() {
//    
//	//Uint32 *pixels = (Uint32 *) Surf_Display->pixels;            // Get the pixels from the Surface
//	//Uint32 color = SDL_MapRGB(Surf_Display->format,40,40,80);
//	for(int x =0; x<Surf_Display->w;x++)
//		for(int y =0; y<Surf_Display->h;y++){
//			int index = (y) * w + x;
//			SetPixelColor(Surf_Display, x, y,
//                          SDL_MapRGB(Surf_Display->format,c[index].x*255,c[index].y*255,c[index].z*255));
//		}
//	SDL_Flip(Surf_Display);
//}
////==============================================================================
//
//void CApp::OnCleanup() {
//	SDL_FreeSurface(Surf_Display);
//    SDL_Quit();
//	//free(tracer);
//}
//
////==============================================================================
//void CApp::OnEvent(SDL_Event* Event) {
//    if(Event->type == SDL_QUIT) {
//        Running = false;
//    }
//}
//
////==============================================================================
//
//int CApp::OnExecute() {
//    if(OnInit() == false) {
//        return -1;
//    }
//    
//    SDL_Event Event;
//    
//    while(Running) {
//        while(SDL_PollEvent(&Event)) {
//            OnEvent(&Event);
//        }
//        
//        OnLoop();
//        OnRender();
//    }
//    
//    OnCleanup();
//    
//    return 0;
//}







//int main(int argc, char *argv[])
//{
//	Uint32 initflags = SDL_INIT_VIDEO;  /* See documentation for details */
//	SDL_Surface *screen;
//	Uint8  video_bpp = 0;
//	Uint32 videoflags = SDL_SWSURFACE;
//	int    done;
//        SDL_Event event;
//
//	/* Initialize the SDL library */
//	if ( SDL_Init(initflags) < 0 ) {
//		fprintf(stderr, "Couldn't initialize SDL: %s\n",
//			SDL_GetError());
//		exit(1);
//	}
//
//	/* Set 640x480 video mode */
//	screen=SDL_SetVideoMode(640,480, video_bpp, videoflags);
//        if (screen == NULL) {
//		fprintf(stderr, "Couldn't set 640x480x%d video mode: %s\n",
//                        video_bpp, SDL_GetError());
//		SDL_Quit();
//		exit(2);
//	}
//
//	done = 0;
//	while ( !done ) {
//
//		/* Check for events */
//		while ( SDL_PollEvent(&event) ) {
//			switch (event.type) {
//
//				case SDL_MOUSEMOTION:
//					break;
//				case SDL_MOUSEBUTTONDOWN:
//					break;
//				case SDL_KEYDOWN:
//					/* Any keypress quits the app... */
//				case SDL_QUIT:
//					done = 1;
//					break;
//				default:
//					break;
//			}
//		}
//	}
//	
//	/* Clean up the SDL library */
//	SDL_Quit();
//	return(0);
//}
