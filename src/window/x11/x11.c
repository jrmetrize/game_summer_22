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
#include "x11.h"

#include "common.h"

struct GS22_X11Driver {
  xcb_connection_t *conn;
  const xcb_setup_t *setup;
  xcb_screen_iterator_t iter;
  xcb_screen_t *screen;
  xcb_window_t win;
};

GS22_X11Driver * GS22_start_x11_display(void) {
  struct GS22_X11Driver *drv = GS22_MALLOC(struct GS22_X11Driver);

  drv->conn = xcb_connect(NULL, NULL);
  drv->setup = xcb_get_setup(drv->conn);
  drv->iter = xcb_setup_roots_iterator(drv->setup);
  drv->screen = drv->iter.data;
  drv->win = xcb_generate_id(drv->conn);
  xcb_create_window(drv->conn, XCB_COPY_FROM_PARENT, drv->win,
      drv->screen->root, 0, 0, 1280, 720, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT,
      drv->screen->root_visual, 0, NULL);
  xcb_map_window(drv->conn, drv->win);
  xcb_flush(drv->conn);

  return drv;
}

void GS22_free_x11(GS22_X11Driver *drv) {
  xcb_disconnect(drv->conn);
  free(drv);
}

xcb_connection_t * GS22_x11_get_connection(GS22_X11Driver *drv) {
  return drv->conn;
}

xcb_window_t GS22_x11_get_window(GS22_X11Driver *drv) {
  return drv->win;
}
