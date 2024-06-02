# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/joltphysics-src"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/joltphysics-build"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/joltphysics-subbuild/joltphysics-populate-prefix"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/joltphysics-subbuild/joltphysics-populate-prefix/tmp"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src/joltphysics-populate-stamp"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src"
  "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src/joltphysics-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src/joltphysics-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Documents/GitHub/Repos/KitzuCore/build/_deps/joltphysics-subbuild/joltphysics-populate-prefix/src/joltphysics-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
