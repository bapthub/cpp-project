#include <string>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>


#include "Application/Application.h"


int main(int argc, char* argv[]) {

    srand ( time(NULL) );

    std::cout << "Starting up the application" << std::endl;

    if (argc != 4)
        throw std::runtime_error("Need three arguments - "
                                 "number of Sheep, number of wolves, "
                                 "simulation time\n");

    Application::init();

    std::cout << "Done with initilization" << std::endl;

    auto app = std::make_unique<Application>(std::stoul(argv[1]), std::stoul(argv[2]));

    std::cout << "Created window" << std::endl;
    int retCode = app->loop(std::stoul(argv[3]));

    std::cout << "Exiting application with code " << retCode << std::endl;
    SDL_Quit();

    return retCode;
}
