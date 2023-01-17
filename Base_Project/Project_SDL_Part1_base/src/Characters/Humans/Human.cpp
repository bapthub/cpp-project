#include "Human.h"
#include "../../Application/Application.h"

human::human(
    const std::string &file_path, 
    SDL_Surface *window_surface_ptr, 
    int human_height, 
    int human_width,
    unsigned speed,
    ObjectType objectType,
    Point point
):
        Rendered(
                20,
                40,
                human_height,
                human_width,
                file_path,
                window_surface_ptr
        )
{
    this->type = objectType;
};