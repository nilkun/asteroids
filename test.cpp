#include <time.h>
#include <SDL2/SDL.h>


main() {

SDL_Rect clip;
SDL_Renderer *renderer;
SDL_Texture *texture;
clip.x = 0;
clip.y = 0;
clip.w = 1;
clip.h = 1;

int msec, i;
clock_t start, diff;

i = 100000;
start = clock();
while(i-- > 0)
{
    SDL_RenderDrawPoint(renderer, 0, 0);
};
diff = clock() - start;

msec = diff * 1000 / CLOCKS_PER_SEC;
fprintf(stdout, "Time taken %d seconds %d milliseconds", msec/1000, msec%1000);

i = 100000;
start = clock();
while(i-- > 0)
{
    SDL_RenderCopy(renderer, texture, &clip, &clip);
}
diff = clock() - start;

msec = diff * 1000 / CLOCKS_PER_SEC;
fprintf(stdout, "Time taken %d seconds %d milliseconds", msec/1000, msec%1000);
}