
#include "Application.h"

Application::Application(unsigned n_sheep, unsigned n_wolf)
{

    window_ptr_ = create_window();
    if (window_ptr_ == nullptr) {
        throw std::runtime_error("application(): " + std::string(SDL_GetError()));
    }
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);

    SDL_Surface *image = IMG_Load(path_img_grass);
    background_ = SDL_ConvertSurface(image, window_surface_ptr_->format, 0);

    SDL_FreeSurface(image);
    print_background();
    ground_ = std::make_unique<Ground>(window_surface_ptr_, n_sheep, n_wolf);

    SDL_UpdateWindowSurface(window_ptr_);

}

Application::~Application()
{
    SDL_FreeSurface(background_);
    SDL_DestroyWindow(window_ptr_);
}

int Application::loop(unsigned window_time)
{
    unsigned start = SDL_GetTicks();
    while (SDL_GetTicks() - start < window_time * 1000)
    {
        if (SDL_PollEvent(&window_event_))
        {
            if (window_event_.type == SDL_QUIT)
            {
                // If SDL_QUIT event is triggered, exit the loop
                break;
            }
        }
        print_background();
        ground_->update();
        SDL_UpdateWindowSurface(window_ptr_);
        SDL_Delay(16);
    }
    return 0;
}

void Application::init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("init():" + std::string(SDL_GetError()));

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw std::runtime_error("init(): SDL_image could not initialize! "
                                 "SDL_image Error: " +
                                 std::string(IMG_GetError()));
}

void Application::print_background()
{
    if(SDL_BlitSurface(background_,NULL,window_surface_ptr_ ,NULL) < 0)
    {
        throw std::runtime_error("can't blit surface");
    }
}

SDL_Window* Application::create_window()
{
    // Initialize SDL window
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_QUIT;

    // Create a window, use frame_width and frame_height, frame_boundary
    SDL_Window* window_ptr = SDL_CreateWindow
            ("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             frame_width, frame_height, flags);
    return window_ptr;
}
