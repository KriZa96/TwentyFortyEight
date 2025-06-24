cmake_minimum_required(VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


project("TwentyFortyEight")


add_executable (TwentyFortyEight "src/Config.h" "src/main.cpp" "src/DisplayManager.cpp" "src/DisplayManager.h" "src/TwentyFortyEightEngine.h" "src/TwentyFortyEightEngine.cpp"   "src/Application.h" "src/Application.cpp" "src/TileRenderer.h" "src/TileRenderer.cpp" "src/Renderer.h" "src/Renderer.cpp" "src/Config.h")
find_package(glad CONFIG REQUIRED)
target_link_libraries(TwentyFortyEight PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(TwentyFortyEight PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(TwentyFortyEight PRIVATE imgui::imgui)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TwentyFortyEight PROPERTY CXX_STANDARD 20)
endif()
