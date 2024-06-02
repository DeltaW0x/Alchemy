# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/sdl-src"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/sdl-build"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/sdl-subbuild/sdl-populate-prefix"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/sdl-subbuild/sdl-populate-prefix/tmp"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/sdl-subbuild/sdl-populate-prefix/src/sdl-populate-stamp"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/sdl-subbuild/sdl-populate-prefix/src"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/sdl-subbuild/sdl-populate-prefix/src/sdl-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/sdl-subbuild/sdl-populate-prefix/src/sdl-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/sdl-subbuild/sdl-populate-prefix/src/sdl-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
