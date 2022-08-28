#include <stdio.h>
#include <SDL.h>

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

int main(int argc, char** argv) {
    printf("hello SDL!\n");

    int width = 640;
    int height = 480;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface* screen = SDL_SetVideoMode(
        width, 
        height, 
        32, 
        SDL_SWSURFACE
    );

    #ifdef TEST_SDL_LOCK_OPTS
        EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
    #endif

    if (SDL_MUSTLOCK(screen)) {
        SDL_LockSurface(screen); 
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
        #ifdef TEST_SDL_LOCK_OPTS
                    int alpha = 255;
        #else
                    int alpha = (i + j) % 255;
        #endif

                    Uint32* pixels = (Uint32*)screen->pixels;
                    SDL_PixelFormat* format = screen->format;

            pixels[i * width + j] = SDL_MapRGBA(
                format, 
                i, 
                j, 
                width + height / 2 - i,
                alpha
            );
        }
    }
    if (SDL_MUSTLOCK(screen)) {
        SDL_UnlockSurface(screen); 
    }

    SDL_Flip(screen);

    printf("you should see a smoothly-colored square - no sharp lines but the square borders!\n");
    printf("and here is some text that should be HTML-friendly: amp: |&| double-quote: |\"| quote: |'| less-than, greater-than, html-like tags: |<cheez></cheez>|\nanother line.\n");

    SDL_Quit();

    return 0;
}