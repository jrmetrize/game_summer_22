add_executable(game_summer_22 main.c)

if(UNIX AND NOT APPLE)
  # Linux
  find_package(X11)
  target_include_directories(game_summer_22 PUBLIC ${X11_xcb_INCLUDE_PATH})
  target_link_libraries(game_summer_22 ${X11_xcb_LIB})
  target_sources(game_summer_22 PUBLIC x11/x11.c)
endif()
