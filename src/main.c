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
#include "window/x11/x11.h"
#include "vk/vk.h"

int main(int argc, char **argv) {
  GS22_X11Driver *x11 = GS22_start_x11_display();
  GS22_VkDriver *vk = GS22_start_vulkan(x11);
  GS22_free_vulkan(vk);
  GS22_free_x11(x11);
  return 0;
}
