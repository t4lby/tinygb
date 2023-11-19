cmake_minimum_required(VERSION 3.0) # setting this is required
set (CMAKE_CXX_STANDARD 11)
project(tinygb)            # this sets the project name

###############################################################################
## file globbing ##############################################################
###############################################################################

file(GLOB_RECURSE src_core src/core/*.c)
file(GLOB_RECURSE src_fenster src/platform/fenster/*.c)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(core ${src_core})

add_executable(tinygb ${src_fenster})
target_link_libraries(tinygb core)

# Just for example add some compiler flags.
# target_compile_options(tinygb PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# This allows to include files relative to the root of the src directory with a <> pair
target_include_directories(core PUBLIC src/include)
target_include_directories(tinygb PUBLIC src/include)

###############################################################################
## dependencies ###############################################################
###############################################################################

# find_package(SDL2 REQUIRED)
# include_directories(tinygb ${SDL2_INCLUDE_DIRS})
# target_link_libraries(tinygb ${SDL2_LIBRARIES} core)