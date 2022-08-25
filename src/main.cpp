//Using SDL and standard IO
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface * gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

bool init_window(){
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return false;
        } 
        else 
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    return true;    
}

SDL_Surface *load_media(const char *filepath)
{
    SDL_Surface *surface = SDL_LoadBMP(filepath);
    if (surface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", filepath, SDL_GetError());
        return (SDL_Surface *)NULL;
    }
    return surface;
}

void close(){
    // free gKeyPressSurfaces
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
    {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
    }

    //Deallocate surface
    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    const char * media = "hello_world.bmp";

    if(!init_window())
    {
        printf("Failed to initialize!\n");
        close();
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = load_media("assets/press.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = load_media("assets/up.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = load_media("assets/down.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = load_media("assets/left.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = load_media("assets/right.bmp");

    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
    {
        if(gKeyPressSurfaces[i] == NULL)
        {
            printf("Failed to load image: %i", i);
            close();
        }
    }


    bool quit = false;
    SDL_Event e;
    SDL_Surface *current_surface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            
            // user requesting to quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            // user presses a key
            if(e.type == SDL_KEYDOWN)
            {
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                        current_surface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                        break;

                    case SDLK_DOWN:
                        current_surface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                        break;
                        
                    case SDLK_LEFT:
                        current_surface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                        break;

                    case SDLK_RIGHT:
                        current_surface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;

                    default:
                        current_surface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                }
            }
        }
        // copy media surface to screen
        SDL_BlitSurface(current_surface, NULL, gScreenSurface, NULL);

        //Update the surface for render
        SDL_UpdateWindowSurface(gWindow);
    }

    // free resources close SDL
    close();

    return 0;
}