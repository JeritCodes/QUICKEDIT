#ifndef BITMAP_H
#define BITMAP_H

#include <SDL.h>

typedef struct {
    SDL_Texture *texture;
    int width;
    int height;
} Bitmap;

typedef struct {
    Bitmap glyphs[128]; // Store printable ASCII characters
} Font;

// Function prototypes
Font *load_font(const char *font_dir, SDL_Renderer *renderer);
void free_font(Font *font);
void render_character(SDL_Renderer *renderer, Font *font, char c, int x, int y, SDL_Color color);
void render_text(SDL_Renderer *renderer, Font *font, const char *text, int x, int y, SDL_Color color);

#endif // BITMAP_H
