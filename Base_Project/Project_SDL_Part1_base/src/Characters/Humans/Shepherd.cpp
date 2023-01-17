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

// Update the Shepherd's position based on the given offsets
void Shepherd::move(int x_offset, int y_offset)
{
    if (point.x + x_offset > 0 && point.x + SHEPHERD_WIDTH + x_offset < frame_width)
    {
        point.x += x_offset;
    }
    
    if (point.y + y_offset > 0 && point.y + SHEPHERD_WIDTH + y_offset < frame_height)
    {
        point.y += y_offset;
    }
}