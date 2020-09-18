
#include "Window.h"

bool Window::init(int aWidth, int aHeight){

	width = aWidth;
	height = aHeight;
	
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		NotifyError( "SDL could not initialize! SDL Error: " + string(SDL_GetError()), GetEnviroment(__FILE__, __FUNCTION__));
		success = false;

	} else{

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			NotifyError( "Warning: Linear texture filtering not enabled!", GetEnviroment(__FILE__, __FUNCTION__));
		}

		//Create window
		this->window = SDL_CreateWindow( "Gley Lancer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
		if( this->window == NULL ){

			NotifyError("Window could not be created! SDL Error: " + string(SDL_GetError()), GetEnviroment(__FILE__, __FUNCTION__));
			success = false;

		} else {

			//Create vsynced renderer for window
			this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

			if( this->renderer == NULL || (SDL_RenderSetLogicalSize(this->renderer,800,600)!=0)){
				NotifyError("Renderer could not be created! SDL Error: " + string(SDL_GetError()), GetEnviroment(__FILE__, __FUNCTION__));
				success = false;

			} else {

				//Initialize renderer color
				SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ){
					NotifyError("SDL_image could not initialize! SDL_image Error " , GetEnviroment(__FILE__, __FUNCTION__));
					success = false;
				}
			}
		}
	}

	// Attach to loggerObserver
    Attach();
	NotifyDebug("Incializada una instancia de Window", GetEnviroment(__FILE__, __FUNCTION__));

	return success;
}



void Window::close(){
    
	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	// Detach to loggerObserver
	NotifyDebug("close de Window llamado.", GetEnviroment(__FILE__, __FUNCTION__));
	Detach();

}

void Window::clearScreen(){

    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(renderer);

}

void Window::renderScreen(){
    
    //Update screen
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::getRenderer(){
    
    return renderer;
}

int Window::getWidth(){ return width; }
int Window::getHeight(){ return height; }