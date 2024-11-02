#include <stdio.h>
#include "SDL.h"
#include <assert.h>
#include <string.h> // Include for memset

#define BOOL u32
#define TRUE 1
#define FALSE 0

#define internal static
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

// The types Uint32, Uint64, Sint32, and Sint64 are specific to SDL and are
// defined in the SDL library.
typedef Uint32 u32;
typedef Uint64 u64;
typedef Sint32 i32;
typedef Sint64 i64;

typedef struct {
    int x;
    int y;
    int w;
    int h;
} rect_t;

internal void FillRect(rect_t rect, u32 pixel_color, u32 *screen_pixels) {
    assert(screen_pixels);
    for (int row = 0; row < rect.h; ++row) {
        for (int col = 0; col < rect.w; ++col) {
            screen_pixels[(row + rect.y) * SCREEN_WIDTH + col + rect.x] = pixel_color;
        }
    }
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // SDL_Window is a structure in SDL that represents a window on the screen.
    // It encapsulates all the information.
    SDL_Window *win = SDL_CreateWindow("QuickType",
                                       // x coordinate
                                       SDL_WINDOWPOS_UNDEFINED,
                                       // y coordinate
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SCREEN_WIDTH,
                                       SCREEN_HEIGHT,
                                       // Flags that specify additional properties of the window
                                       0);
    assert(win);

    // SDL_Renderer is a struct that handles all rendering. It is tied to a SDL_Window
    // so it can only render within that SDL_Window. It also keeps track of the settings
    // related to the rendering.
    SDL_Renderer *renderer = SDL_CreateRenderer(win,
                                                // SDL automatically picks the first rendering driver
                                                // that works well with the flags you specified
                                                0,
                                                SDL_RENDERER_SOFTWARE);
    assert(renderer);

    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    SDL_Texture *screen = SDL_CreateTexture(renderer,
                                            // The pixel format of the texture.
                                            format->format,
                                            // How the texture will be used and how frequently its contents
                                            // will be updated. Here, the texture will change frequently.
                                            SDL_TEXTUREACCESS_STREAMING,
                                            SCREEN_WIDTH,
                                            SCREEN_HEIGHT);
    // Asserts that the texture was created successfully
    assert(screen);

    // Allocate memory for the screen pixels
    // Each pixel is represented by a 32-bit unsigned integer (u32)
    // The total number of pixels is SCREEN_WIDTH * SCREEN_HEIGHT
    // calloc initializes all bits to zero, resulting in a black screen
    u32 *screen_pixels = (u32*)calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(u32));
    assert(screen_pixels);

    rect_t square = {0, 0, 30, 30};
    square.x = SCREEN_WIDTH / 2 - square.w / 2;
    square.y = SCREEN_HEIGHT / 2 - square.h / 2;
    u32 pixel_color = SDL_MapRGB(format, 0, 0, 255);
    FillRect(square, pixel_color, screen_pixels);

    BOOL done = FALSE;
    BOOL pressedUp = FALSE;
    BOOL pressedDown = FALSE;
    BOOL pressedRight = FALSE;
    BOOL pressedLeft = FALSE;

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = TRUE;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode code = event.key.keysym.sym;
                switch (code) {
                    case SDLK_ESCAPE:
                        done = TRUE;
                        break;
                    case SDLK_UP:
                        pressedUp = TRUE;
                        break;
                    case SDLK_DOWN:
                        pressedDown = TRUE;
                        break;
                    case SDLK_LEFT:
                        pressedLeft = TRUE;
                        break;
                    case SDLK_RIGHT:
                        pressedRight = TRUE;
                        break;
                    default:
                        break;
                }
            }
            if (event.type == SDL_KEYUP) {
                SDL_Keycode code = event.key.keysym.sym;
                switch (code) {
                    case SDLK_UP:
                        pressedUp = FALSE;
                        break;
                    case SDLK_DOWN:
                        pressedDown = FALSE;
                        break;
                    case SDLK_LEFT:
                        pressedLeft = FALSE;
                        break;
                    case SDLK_RIGHT:
                        pressedRight = FALSE;
                        break;
                    default:
                        break;
                }
            }
        }

        memset(screen_pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u32));
        if (pressedUp) {
            square.y -= 1;
        }
        if (pressedDown) {
            square.y += 1;
        }
        if (pressedRight) {
            square.x += 1;
        }
        if (pressedLeft) {
            square.x -= 1;
        }
        FillRect(square, pixel_color, screen_pixels);

        SDL_UpdateTexture(screen, NULL, screen_pixels, SCREEN_WIDTH * sizeof(u32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, screen, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(14);
    }


    free(screen_pixels);
    SDL_FreeFormat(format);
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
