# cmake_minimum_required(VERSION 3.10)
# project(MediaReader C)

# # find_package(PNG REQUIRED)

# # Add libmad
# # find_path(MAD_INCLUDE_DIR mad.h)
# # find_library(MAD_LIBRARY mad)

# # Add libmp3lame
# # find_path(MP3LAME_INCLUDE_DIR lame/lame.h)
# # find_library(MP3LAME_LIBRARY mp3lame)

# add_executable(media_reader main.c)

# target_include_directories(media_reader PRIVATE
#     # ${PNG_INCLUDE_DIR}
#     # ${MAD_INCLUDE_DIR}
#     # ${MP3LAME_INCLUDE_DIR}
# )

# target_link_libraries(media_reader PRIVATE
#     # ${PNG_LIBRARY}
#     # ${MAD_LIBRARY}
#     # ${MP3LAME_LIBRARY}
# )



cmake_minimum_required(VERSION 3.10)
project(WavStenography C)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s")

# Add the executable
add_executable(wav_stenography main.c)