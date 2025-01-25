#ifndef __H_GAME_CONTEXT__
#define __H_GAME_CONTEXT__
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <vulkan/vulkan.h>

typedef struct {
  int id;
  int width;
  int height;
  char *title;
  SDL_Window *sdlwindow;
} window_t;

typedef struct {
  VkInstance instance;
} vulkan_t;

typedef struct {
  window_t window;
  vulkan_t vulkan;
  bool was_init;
  bool running;
} game_t;

game_t default_game();
void create_window(game_t *game, int width, int height, const char *title);
bool should_run(const game_t *game);
void destroy_game(game_t *game);

#endif /* __H_GAME_CONTEXT__ */
