# C++ Project for EPITA course

## Compile the project

Here are the steps to compile the project on Linux after cloning the repository :

First get to the directory where the project will be built : \
`cd cpp-project/Base_Project/Project/`

Then create a new *build* directory : \
`mkdir build`

Go within this new directory : \
`cd build`

Use the cmake program to create the necessary files to compile : \
`cmake ..`

And compile using the make command : \
`make`

## Launch the project

You can now launch the game using 3 arguments : \
`./SDL_project number_of_Sheep number_of_wolves simulation_time`

Example : \
`./SDL_project 2 2 30`

## Informations

The score corresponds to the number of sheeps still alive at the end of the simulation time. \
It will be printed at the end of the game.