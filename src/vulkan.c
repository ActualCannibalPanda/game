#include "game/vulkan.h"

#include <stdint.h>
#include <stdio.h>

#ifdef _DEBUG
const char *VALIDATION_LAYERS[] = {
    "VK_LAYER_KHRONOS_validation",
};
const int VALIDATION_COUNT =
    sizeof(VALIDATION_LAYERS) / sizeof(VALIDATION_LAYERS[0]);

bool checkValidationLayerSupport() {
  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, NULL);

  VkLayerProperties layers[layer_count];
  vkEnumerateInstanceLayerProperties(&layer_count, layers);

  for (int i = 0; i < VALIDATION_COUNT; ++i) {
    bool layer_found = false;
    const char *layer_name = VALIDATION_LAYERS[i];

    for (int j = 0; j < layer_count; ++j) {
      VkLayerProperties layer_property = layers[j];
      if (strcmp(layer_name, layer_property.layerName) == 0) {
        layer_found = true;
        break;
      }
    }

    if (!layer_found) {
      return false;
    }
  }

  return true;
}
#endif

static bool _create_instance(game_t *game) {
#ifdef _DEBUG
  if (!checkValidationLayerSupport()) {
    return false;
  }
#endif

  VkApplicationInfo app_info = {0};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = game->window.title;
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "No Engine";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;

  uint32_t sdl_extenstion_count = 0;
  const char *const *sdl_extenstions;

  sdl_extenstions = SDL_Vulkan_GetInstanceExtensions(&sdl_extenstion_count);

  VkInstanceCreateInfo create_info = {0};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
  create_info.enabledExtensionCount = sdl_extenstion_count;
  create_info.ppEnabledExtensionNames = sdl_extenstions;
#ifndef _DEBUG
  create_info.enabledLayerCount = 0;
#else
  create_info.enabledLayerCount = VALIDATION_COUNT;
  create_info.ppEnabledLayerNames = VALIDATION_LAYERS;
#endif

  if (vkCreateInstance(&create_info, NULL, &game->vulkan.instance) !=
      VK_SUCCESS) {
    return false;
  }
  return true;
}

void init_vulkan(game_t *game) {
  if (!_create_instance(game)) {
    fprintf(stderr, "Failed to create instance\n");
    // TODO: Do error stuff
  }
}

void deinit_vulkan(game_t *game) {
  vkDestroyInstance(game->vulkan.instance, NULL);
}
