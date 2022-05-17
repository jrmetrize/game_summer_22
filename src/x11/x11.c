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
#include <xcb/xcb.h>

void start_x11_display(void) {
  xcb_connection_t *conn;
  const xcb_setup_t *setup;
  xcb_screen_iterator_t iter;
  xcb_screen_t *screen;
  xcb_window_t win;

  conn = xcb_connect(NULL, NULL);
  setup = xcb_get_setup(conn);
  iter = xcb_setup_roots_iterator(setup);
  screen = iter.data;
  win = xcb_generate_id(conn);
  xcb_create_window(conn, XCB_COPY_FROM_PARENT, win, screen->root,
    0, 0, 1280, 720, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
    0, NULL);
  xcb_map_window(conn, win);
  xcb_flush(conn);

  pause();

  xcb_disconnect(conn);
}
