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
#ifndef GS22_X11_H
#define GS22_X11_H

#include <xcb/xcb.h>

struct GS22_X11Driver;
typedef struct GS22_X11Driver GS22_X11Driver;

GS22_X11Driver * GS22_start_x11_display(void);
void GS22_free_x11(GS22_X11Driver *drv);

xcb_connection_t * GS22_x11_get_connection(GS22_X11Driver *drv);
xcb_window_t GS22_x11_get_window(GS22_X11Driver *drv);

#endif
