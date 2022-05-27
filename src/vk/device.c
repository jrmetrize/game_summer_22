/*
 * game_summer_22
 * Copyright (C) 2022  jrMetrize
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "vk.h"
#include "common.h"

#define VK_USE_PLATFORM_XCB_KHR
#include <vulkan/vulkan.h>

struct GS22_VkDriver {
  VkInstance instance;
  VkPhysicalDevice physical_device;
  VkDevice device;
  VkSurfaceKHR surface;
};

static int init_instance(struct GS22_VkDriver *drv) {
#if GS22_DEBUG
  const char *layer[] = {
    "VK_LAYER_KHRONOS_validation"
  };
#endif

  /* TODO: Handle extensions dynamically. */
  const char *ext[] = {
    "VK_KHR_surface",
    "VK_KHR_xcb_surface"
  };

  /* TODO: Check for layers and extensions. */

  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "gs22";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "gs22e";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo inst_info = {};
  inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  inst_info.pApplicationInfo = &app_info;
  inst_info.enabledExtensionCount = 2;
  inst_info.ppEnabledExtensionNames = ext;

#if GS22_DEBUG
  inst_info.enabledLayerCount = 1;
  inst_info.ppEnabledLayerNames = layer;
#else
  inst_info.enabledLayerCount = 0;
#endif

  if (VK_SUCCESS != vkCreateInstance(&inst_info, NULL, &drv->instance))
    return 1;
  return 0;
}

static int init_physical_device(struct GS22_VkDriver *drv) {
  uint32_t dev_count;
  vkEnumeratePhysicalDevices(drv->instance, &dev_count, NULL);
  if (0 == dev_count)
    return 1;
  VkPhysicalDevice *devs = malloc(sizeof(VkPhysicalDevice) * dev_count);
  vkEnumeratePhysicalDevices(drv->instance, &dev_count, devs);

  /* TODO: Choose the best device. */
  drv->physical_device = devs[0];
  free(devs);
  return 0;
}

static int init_device(struct GS22_VkDriver *drv) {
  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(drv->physical_device,
      &queue_family_count, NULL);

  VkQueueFamilyProperties *queue_families =
      malloc(sizeof(VkQueueFamilyProperties) * queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(drv->physical_device,
      &queue_family_count, queue_families);

  uint32_t graphics_family;
  int i = 0;
  for (int j = 0; j < queue_family_count; ++j) {
    if (queue_families[j].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      graphics_family = i;
    }
    i++;
  }
  free(queue_families);

  float queue_priority = 1.0f;

  VkDeviceQueueCreateInfo queue_info = {};
  queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_info.queueFamilyIndex = graphics_family;
  queue_info.queueCount = 1;
  queue_info.pQueuePriorities = &queue_priority;

  VkPhysicalDeviceFeatures features = {};

  VkDeviceCreateInfo dev_info = {};
  dev_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  dev_info.pQueueCreateInfos = &queue_info;
  dev_info.queueCreateInfoCount = 1;
  dev_info.pEnabledFeatures = &features;
  dev_info.enabledExtensionCount = 0;
  dev_info.enabledLayerCount = 0;
  if (VK_SUCCESS != vkCreateDevice(drv->physical_device, &dev_info, NULL,
      &drv->device))
    return 1;
  return 0;
}

static int init_surface(struct GS22_VkDriver *drv, GS22_X11Driver *x11) {
  VkXcbSurfaceCreateInfoKHR surface_info = {};
  surface_info.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
  surface_info.connection = GS22_x11_get_connection(x11);
  surface_info.window = GS22_x11_get_window(x11);
  if (VK_SUCCESS != vkCreateXcbSurfaceKHR(drv->instance, &surface_info, NULL,
      &drv->surface))
    return 1;
  return 0;
}

GS22_VkDriver * GS22_start_vulkan(GS22_X11Driver *x11) {
  struct GS22_VkDriver *drv = GS22_MALLOC(struct GS22_VkDriver);
  if (NULL == drv)
    return NULL;
  if (0 != init_instance(drv)) {
    free(drv);
    return NULL;
  }
  if (0 != init_physical_device(drv)) {
    free(drv);
    return NULL;
  }
  if (0 != init_device(drv)) {
    free(drv);
    return NULL;
  }
  init_surface(drv, x11); /* TODO: Handle failure properly. */
  return drv;
}

void GS22_free_vulkan(GS22_VkDriver *drv) {
  if (NULL == drv)
    return;
  vkDestroySurfaceKHR(drv->instance, drv->surface, NULL);
  vkDestroyDevice(drv->device, NULL);
  vkDestroyInstance(drv->instance, NULL);
  free(drv);
}
