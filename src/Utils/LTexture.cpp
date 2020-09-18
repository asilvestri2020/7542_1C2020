#include "LTexture.h"


LTexture::LTexture(SDL_Renderer* gRenderer){
	//Initialize
	this->mTexture = NULL;
	this->mWidth = 0;
	this->mHeight = 0;
	this->gRenderer = gRenderer;
	this->scrollingOffset = 0;

	// Attach to loggerObserver
    Attach();
	NotifyDebug("Incializado LTexture", GetEnviroment(__FILE__, __FUNCTION__));
}

LTexture::~LTexture(){
	// Detach to loggerObserver
	NotifyDebug("Destructor de LTexture llamado.", GetEnviroment(__FILE__, __FUNCTION__));
	Detach();

	//Deallocate
	this->free();
}

bool LTexture::loadFromFile( std::string path, int width, int height){
	//Get rid of preexisting texture
	this->free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	std:string enviroment =  this->GetEnviroment(__FILE__, __FUNCTION__);

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	NotifyDebug("Cargando SDL_surface",enviroment);

	if( loadedSurface == NULL ) {
		string error = "No se pudo cargar la imagen " + path + " con el SDL_image Error: " +  IMG_GetError();
		NotifyError(error,enviroment);
	} else {
		NotifyDebug("Cargada SDL_surface",enviroment);

		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( this->gRenderer, loadedSurface );
		NotifyDebug("Cargando textura del archivo" + path,enviroment);

		if( newTexture == NULL ){
			string error = "No se pudo crear la textura del archivo: " + path + " con el SDL_image Error: " +  IMG_GetError();
			NotifyError(error,enviroment);
		} else  {
			NotifyDebug("Se cargo la textura del archivo: " + path,enviroment);

			if(width == 0 ){
				this->mWidth = loadedSurface->w;
			}else{
				this->mWidth = width;
			}

			if(height == 0){
				this->mHeight = loadedSurface->h;
			}else{
				this->mHeight = height;
			}
			
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
		NotifyDebug("Liberda la SDL_surface usada",enviroment);
	}

	//Return success
	this->mTexture = newTexture;
	return this->mTexture != NULL;
}

int LTexture::getScrollingOffset(){
	return this->scrollingOffset;
}

void LTexture::setScrollingOffset(int scrollingOffset){
	this->scrollingOffset = scrollingOffset;
}

void LTexture::setVelocity(int velocity){
	this->velocity = velocity;
}

int LTexture::getVelocity(){
	return this->velocity;
}


void LTexture::free(){
	//Free texture if it exists
	if( this->mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		this->mTexture = NULL;
		this->mWidth = 0;
		this->mHeight = 0;
		this->scrollingOffset= 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
	//Modulate texture rgb
	SDL_SetTextureColorMod( this->mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending ){
	//Set blending function
	SDL_SetTextureBlendMode( this->mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha ){
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( this->mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, this->mWidth, this->mHeight };

	//Set clip rendering dimensions
	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( this->gRenderer, this->mTexture, clip, &renderQuad, angle, center, flip );

}

int LTexture::getWidth(){
	return this->mWidth;
}

int LTexture::getHeight(){
	return this->mHeight;
}