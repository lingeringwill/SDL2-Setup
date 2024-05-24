#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window* gWindow = NULL;

SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gHelloWorld = NULL;



SDL_Surface* gCurrentSurface = NULL;



//Key press surfaces constants
    
typedef enum KeyPressSurfaces 
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
} KeyPressSurfaces;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

SDL_Surface* loadSurface ( const char* fileName ) 
{
  //The final optimized image
  SDL_Surface* optimizedSurface = NULL;

  //Load image at specified path
  SDL_Surface* loadedSurface = SDL_LoadBMP( fileName );

  if ( !loadedSurface ) {
    printf( "Unable to loead image %s! SDL Error: %s\n", fileName, SDL_GetError() );

  } else {
    //convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
    if ( !optimizedSurface ) {
        printf( "Unable to optimize image %s! SDL Error: %s\n", fileName, SDL_GetError() );
        exit( 1 );

    } 

    //Get rid of old loaded surfae
    SDL_FreeSurface( loadedSurface );
  }

  return optimizedSurface;
}




bool loadMedia()
{
    //Loading successflag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("src\\press.bmp");

    if ( gKeyPressSurfaces [ KEY_PRESS_SURFACE_DEFAULT ] == NULL ) 
    {
        printf( "Failed to load default image!\n");
        success = false;
    }

    //load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "src\\up.bmp" );
       if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }


    //load down surface 
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface("src\\down.bmp");
    if ( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL ) 
    {
        printf( "Failed to load down image!\n");
        success = false;
    }

    //load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "src\\left.bmp");
    if ( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL ) {
        printf("failed to load left image!\n");
        success = false;
    }

    //load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "src\\right.bmp" );
      if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;

}

bool init() 
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initalize! SDL_ERROR: %S\n", SDL_GetError );
        success = false;
    } else { // if it didn't fail keep going
        // set window

        gWindow = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        
        if ( gWindow == NULL ) {
            printf( "Window could not be created! SDL_Error: %s", SDL_GetError() );
        } else {
            // set surface
           
            gScreenSurface = SDL_GetWindowSurface( gWindow );

        }

        if ( !loadMedia() ) {
            printf(" cannot load media ");
            exit( 1 );
        }
    }

    return success;
}

void Close()
{
    //Deallocate the surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
}



int main( int argc, char* argv[] ) {
    //Main loop flag
    bool quit = false;
    
    //Event handler
    SDL_Event e;

    //Set defualt current surface
    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
        return 1;
    }
    else
    {
   
    while ( !quit ) {
        
        while ( SDL_PollEvent( &e ) != 0 ) {
            
            //User wants to quit
            if ( e.type == SDL_QUIT ) 
            {
                quit = true;
            }

            // User presses a key
            else if ( e.type == SDL_KEYDOWN ) {
                switch ( e.key.keysym.sym ) {
                    case SDLK_UP:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                    break;
                    
                    case SDLK_DOWN:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                    break;

                    case SDLK_LEFT:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                    break;

                    case SDLK_RIGHT:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                    break;

                    defulat:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                    break;
                }                
            }
        } 
        
        SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );

        //update the surface
        SDL_UpdateWindowSurface( gWindow );
        
    }
}

   Close();

   return EXIT_SUCCESS;

}   

// SDL_Texture* loadTexture( const char* );
// //the window we will be rendering to
// SDL_Window* gWindow = NULL;

// // the window rendered
// SDL_Renderer* gRenderer = NULL;

// //current displayed texture
// SDL_Texture* gTexture = NULL;

// bool init() {
//     bool success = true;

//     if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
//         printf( " unable to initialize SDL, SDL_Error: %s\n", SDL_GetError() );
//         success = false;
//     } else {
//         //Create renderer for window
//         gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
//         if ( !gRenderer ) {
//             printf( "unable to create Renderer, SDL_Error: %s\n", SDL_GetError() );
//             success = false;
//         } else {
//             //Initialize renderer color
//             SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF,0xFF, 0xFF );

//             //Initialize PNG loading
//             int imgFlags = IMG_INIT_PNG;

//             if ( !( IMG_INIT( imgFlags )))
//         }
//     }
// }
