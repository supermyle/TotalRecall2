//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gTitleImage = NULL;

int main( int argc, char* args[] ){
	printf("Game launched\n"); //DEBUG STATEMENT 
    //Start up SDL and create window
    if( !init() ){
        printf( "Failed to initialize!\n" );
    }else{
        //Load media
        if( !loadMedia() ){
            printf( "Failed to load media!\n" );
        }else{
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

			//While application is running
            while( !quit ){
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 ){
                    //User requests quit (Xs out the window)
                    if( e.type == SDL_QUIT ){
                        quit = true;
                    }
                }
				//Apply the image
				SDL_BlitSurface( gTitleImage, NULL, gScreenSurface, NULL );

				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
        }
    }
	printf("Exting window\n"); //DEBUG STATEMENT
    //Free resources and close SDL
    close();

    return 0;
}

bool init(){
	//Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }else{
        //Create window
        gWindow = SDL_CreateWindow( "Total Recall 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else{
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia(){
	//Loading success flag
    bool success = true;

    //Load splash image
    gTitleImage = SDL_LoadBMP( "Resources/TitleScreen.bmp" );
    if( gTitleImage == NULL ){
        printf( "Unable to load image %s! SDL Error: %s\n", "Resources/TitleScreen.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void close(){
	//Deallocate surface
    SDL_FreeSurface( gTitleImage );
    gTitleImage = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
