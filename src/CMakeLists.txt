add_executable(game_summer_22 main.c)

target_include_directories(game_summer_22 PRIVATE ./)

add_compile_definitions(GS22_DEBUG)

if(UNIX AND NOT APPLE)
  # Linux
  find_package(X11)
  find_package(Vulkan)
  target_include_directories(game_summer_22 PUBLIC ${X11_xcb_INCLUDE_PATH}
      ${Vulkan_INCLUDE_DIR})
  target_link_libraries(game_summer_22 ${X11_xcb_LIB} ${Vulkan_LIBRARY})
  target_sources(game_summer_22 PUBLIC vk/device.c)
  target_sources(game_summer_22 PUBLIC window/x11/x11.c)
endif()
