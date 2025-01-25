#include "game/context.h"
#include <string.h>

game_t default_game() {
  return (game_t){.window =
                      (window_t){
                          .id = 0,
                          .width = 0,
                          .height = 0,
                          .title = NULL,
                          .sdlwindow = NULL,
                      },
                  .was_init = false,
                  .running = false};
}

static char *stringdup(const char *src) {
  char *dest = malloc(strlen(src) + 1);
  if (dest) {
    memcpy(dest, src, strlen(src) + 1);
  }
  return dest;
}

void create_window(game_t *game, int width, int height, const char *title) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return;
  }
  SDL_Vulkan_LoadLibrary(NULL);

  game->window.width = width;
  game->window.height = height;
  game->window.title = stringdup(title);

  game->window.sdlwindow =
      SDL_CreateWindow(game->window.title, game->window.width,
                       game->window.height, SDL_WINDOW_VULKAN);
  if (game->window.sdlwindow == NULL) {
    return;
  }

  game->was_init = true;
  game->running = true;
}

bool should_run(const game_t *game) { return game->running; }

void destroy_game(game_t *game) {
  if (game->window.title != NULL) {
    free(game->window.title);
    game->window.title = NULL;
  }
  game->running = false;

  if (game->window.sdlwindow != NULL) {
    SDL_DestroyWindow(game->window.sdlwindow);
    game->window.sdlwindow = NULL;
  }

  SDL_Vulkan_UnloadLibrary();

  SDL_Quit();
}
