#include "game/context.h"
#include "game/vulkan.h"

#include <bigc/string.h>

static int WindowWidth = 800;
static int WindowHeight = 600;

int main(int argc, char **argv) {
  game_t game = default_game();
  create_window(&game, WindowWidth, WindowHeight, "Game");
  init_vulkan(&game);

  while (should_run(&game)) {
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0) {
      if (event.type == SDL_EVENT_QUIT) {
        game.running = false;
      }
    }
  }

  deinit_vulkan(&game);
  destroy_game(&game);

  return 0;
}
