#!/bin/sh

if [ -n "$1" ] && [ -n "$2" ] && [ -n "$3" ]; then
  cd Base_Project
  mkdir build
  cd build
  cmake ..
  make
  cd Project
  ./SDL_project $1 $2 $3
else
  echo "You must specifiy 3 arguments"
  echo 'Usage: ./launch.sh n_sheeps n_wolfs max_game_duration'
fi



