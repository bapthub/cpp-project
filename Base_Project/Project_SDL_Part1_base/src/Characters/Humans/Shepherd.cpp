#include "Shepherd.h"
#include "../../Application/Application.h"

Shepherd::Shepherd(SDL_Surface *window_surface_ptr) : human(
        path_img_shepherd,
        window_surface_ptr,
        SHEPHERD_HEIGHT,
        SHEPHERD_WIDTH,
        1,
        ObjectType::SHEPHERD,
        point
)
{

}

// Update the animal's position based on the given offsets
void Shepherd::move(int x_offset, int y_offset)
{
    point.x += x_offset;
    point.y += y_offset;
}