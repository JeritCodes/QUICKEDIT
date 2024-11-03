#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include "bitmap.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "SDL_image could not initialize: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("QuickEdit", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        return 1;
    }

    const char *fontPath = "src/font_generation/output_images"; // Correct path here
    Font *font = load_font(fontPath, renderer);
    if (font == NULL) {
        fprintf(stderr, "Font loading failed!\n");
        return 1;
    }

    SDL_Color textColor = {255, 255, 255, 255}; // Set text color (white)
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear to black
        SDL_RenderClear(renderer);
        render_text(renderer, font, "The quick brown fox jumps over the lazy dog", 50, 50, textColor);
        SDL_RenderPresent(renderer);
    }

    free_font(font); // Free the font
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
