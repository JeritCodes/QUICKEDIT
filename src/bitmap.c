#include <SDL_image.h>
int main(int argc, char *argv[]) { 

    // Initialize SDL_image with support for the image formats you need.
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_BMP; // For PNG, JPG, and BMP support.
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 1; // Or handle the error appropriately
    }

    // ... rest of your initialization ...
}

Bitmap* load_bitmap(const char* filepath) {
    SDL_Surface* loadedSurface = IMG_Load(filepath);  // Load image using SDL_image
    if(loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", filepath, IMG_GetError() );
        return NULL; // Or handle error as needed
    }
    // Convert to a consistent pixel format if necessary.
    SDL_Surface* optimizedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
    if (optimizedSurface == NULL){
      printf("Error converting surface to RGBA8888: %s\n", SDL_GetError());
      return NULL;
    }


    Bitmap* bitmap = (Bitmap*)malloc(sizeof(Bitmap));
    if (bitmap == NULL) {
        printf("Failed to allocate memory for Bitmap\n");
        SDL_FreeSurface(optimizedSurface); // Clean up before exiting
        SDL_FreeSurface(loadedSurface); // Clean up before exiting
        return NULL; // or another error handling approach
    }
    bitmap->width = optimizedSurface->w;
    bitmap->height = optimizedSurface->h;

    //Allocate the final pixel data destination
    bitmap->pixels = (Uint32*)malloc(optimizedSurface->pitch * optimizedSurface->h);
    if (bitmap->pixels == NULL) {
        printf("Failed to allocate memory for pixel data\n");
        free(bitmap);
        SDL_FreeSurface(optimizedSurface); // Clean up before exiting
        SDL_FreeSurface(loadedSurface); // Clean up before exiting
        return NULL; // or another error handling approach
    }

    memcpy(bitmap->pixels, optimizedSurface->pixels, optimizedSurface->pitch * optimizedSurface->h);




    SDL_FreeSurface(optimizedSurface);
    SDL_FreeSurface(loadedSurface);

    return bitmap;
}
