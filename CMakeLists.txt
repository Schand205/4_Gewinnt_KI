# Mindestversion CMake
cmake_minimum_required(VERSION 3.10)

# Projektname
project(4_Gewinnt_MiniMax VERSION 1.0)

# C-Standard setzen
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# SDL2
find_package(SDL2 REQUIRED)

# Source Dateien
add_executable(MyExecutable
	4Gewinnt.c
	minimax.c
	rand_bot.c
	spiellogik.c
	loop_logik.c
	minimax_logik.c
	selbst_spielen.c
	suchen_bot.c
)
# Include Dateien(Header)
target_include_directories(MyExecutable
	PRIVATE
		${PROJECT_SOURCE_DIR}
		${SDL2_INCLUDE_DIRS}
)
# SDL2 linken
target_link_libraries(MyExecutable
	PRIVATE
		${SDL2_LIBRARIES}
)
