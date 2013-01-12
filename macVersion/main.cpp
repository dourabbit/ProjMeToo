
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
#include <CApp.h>
#include <SDLHelper.hpp>
#include <pathTracerSplitted.hpp>
//#include <Tracer/pathTracer.hpp>
#include "pathTracerSplitted.hpp"
//#include <Test.h>

//Mac Entry
int main(int argc, char* argv[]) {
    CApp theApp;
    return theApp.OnExecute();
//    Vec* c = new Vec[100*100];
//    
//    Tracer::PathTracerSplitted* tracer = new Tracer::PathTracerSplitted();
//    tracer->Render(c);
    return 0;
}
