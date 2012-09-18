//==============================================================================
#include "CApp.h"
#include "SDLHelper.hpp"

//==============================================================================
CApp::CApp() {
    Surf_Display = NULL;
    Running = true;
	tracer = new Tracer::PathTracerSplitted();
	tracer->Initialize();
}
//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
	w = h= 512;
    if((Surf_Display = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

	SDL_FillRect(Surf_Display, NULL, 0); 
	SDL_Flip(Surf_Display);

	SDL_Thread *thread;
	int threadReturnValue;

	
	c = new Vec[w * h];
	tracer->width  = w;
	tracer->height = h;
	thread = SDL_CreateThread(tracer->Render,  (void *)c);

    return true;
}
//==============================================================================

void CApp::OnLoop() {
}
//==============================================================================

void CApp::OnRender() {

	//Uint32 *pixels = (Uint32 *) Surf_Display->pixels;            // Get the pixels from the Surface
	//Uint32 color = SDL_MapRGB(Surf_Display->format,40,40,80);
	for(int x =0; x<Surf_Display->w;x++)
		for(int y =0; y<Surf_Display->h;y++){
			int index = (y) * w + x;
			SetPixelColor(Surf_Display, x, y, 
				SDL_MapRGB(Surf_Display->format,c[index].x*255,c[index].y*255,c[index].z*255));
		}
	SDL_Flip(Surf_Display);
}
//==============================================================================

void CApp::OnCleanup() {
	SDL_FreeSurface(Surf_Display);
    SDL_Quit();
	free(tracer);
}

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
    }
}

//==============================================================================

int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

//==============================================================================
int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();
}

