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
#ifndef GS22_VK_H
#define GS22_VK_H

#include "window/x11/x11.h"

struct GS22_VkDriver;
typedef struct GS22_VkDriver GS22_VkDriver;

GS22_VkDriver * GS22_start_vulkan(GS22_X11Driver *x11);
void GS22_free_vulkan(GS22_VkDriver *drv);

#endif
