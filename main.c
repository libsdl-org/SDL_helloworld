#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static int setup_program(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        SDL_Log("SDL_Init(SDL_INIT_VIDEO) failed: %s", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Hello SDL", 640, 480, 0);
    if (!window) {
        SDL_Log("SDL_CreateWindow() failed: %s", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer() failed: %s", SDL_GetError());
        return -1;
    }

    return 0;
}

static void mainloop(void)
{
    SDL_FRect mouseposrect;
    Uint8 r;
    SDL_bool keep_going = SDL_TRUE;
    SDL_Event event;

    mouseposrect.x = mouseposrect.y = -1000;  /* -1000 so it's offscreen at start */
    mouseposrect.w = mouseposrect.h = 50;

    /* run the program until told to stop. */
    while (keep_going) {

        /* run through all pending events until we run out. */
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:  /* triggers on last window close and other things. End the program. */
                    keep_going = SDL_FALSE;
                    break;

                case SDL_EVENT_KEY_DOWN:  /* quit if user hits ESC key */
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        keep_going = SDL_FALSE;
                    }
                    break;

                case SDL_EVENT_MOUSE_MOTION:  /* keep track of the latest mouse position */
                    /* center the square where the mouse is */
                    mouseposrect.x = event.motion.x - (mouseposrect.w / 2);
                    mouseposrect.y = event.motion.y - (mouseposrect.h / 2);
                    break;
            }
        }

        /* fade between shades of red every 3 seconds, from 0 to 255. */
        r = (Uint8) ((((float) (SDL_GetTicks() % 3000)) / 3000.0f) * 255.0f);
        SDL_SetRenderDrawColor(renderer, r, 0, 0, 255);

        /* you have to draw the whole window every frame. Clearing it makes sure the whole thing is sane. */
        SDL_RenderClear(renderer);  /* clear whole window to that fade color. */

        /* set the color to white */
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        /* draw a square where the mouse cursor currently is. */
        SDL_RenderFillRect(renderer, &mouseposrect);

        /* put everything we drew to the screen. */
        SDL_RenderPresent(renderer);
    }
}

static void shutdown_program(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


/* this is always a main() function, even if you're on a platform that uses
   something else. SDL_main.h takes care of figuring out the details and
   making sure the program starts here. */
int main(int argc, char **argv)
{
    if (setup_program(argc, argv) == 0) {
        mainloop();
    }
    shutdown_program();
    return 0;
}

