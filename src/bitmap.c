#include "bitmap.h"
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

Font *load_font(const char *font_dir, SDL_Renderer *renderer) {
    Font *font = malloc(sizeof(Font));
    if (!font) {
        perror("Memory allocation failed for font");
        return NULL;
    }

    for (int i = 33; i < 127; i++) {
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/%d.png", font_dir, i);
        font->glyphs[i].texture = IMG_LoadTexture(renderer, file_path);

        if (!font->glyphs[i].texture) {
            fprintf(stderr, "Error loading character %c: %s\n", (char)i, SDL_GetError());
            font->glyphs[i].width = 0;
            font->glyphs[i].height = 0;
        } else {
            SDL_QueryTexture(font->glyphs[i].texture, NULL, NULL, &font->glyphs[i].width, &font->glyphs[i].height);
        }
    }
    return font;
}

void free_font(Font *font) {
    if (font) {
        for (int i = 0; i < 128; ++i) {
            SDL_DestroyTexture(font->glyphs[i].texture);
        }
        free(font);
    }
}

void render_character(SDL_Renderer *renderer, Font *font, char c, int x, int y, SDL_Color color) {
    if (c < 33 || c >= 127) return; // Ignore invalid characters

    Bitmap *glyph = &font->glyphs[(int)c];
    if (glyph->texture == NULL) return; // No texture available

    SDL_Rect dstrect = { x, y, glyph->width, glyph->height };
    SDL_SetTextureColorMod(glyph->texture, color.r, color.g, color.b);
    SDL_RenderCopy(renderer, glyph->texture, NULL, &dstrect);
}

void render_text(SDL_Renderer *renderer, Font *font, const char *text, int x, int y, SDL_Color color) {
    int current_x = x;
    for (int i = 0; text[i] != '\0'; ++i) {
        render_character(renderer, font, text[i], current_x, y, color);
        current_x += font->glyphs[(int)text[i]].width; // Move the current x position
    }
}
