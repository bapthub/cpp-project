#include "Application.h"

Application::Application(unsigned n_sheep, unsigned n_wolf)
{

    window_ptr_ = create_window();
    if (window_ptr_ == nullptr)
    {
        throw std::runtime_error("application(): " + std::string(SDL_GetError()));
    }
    window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);

    SDL_Surface *image = IMG_Load(path_img_grass);
    background_ = SDL_ConvertSurface(image, window_surface_ptr_->format, 0);

    SDL_FreeSurface(image);
    print_background();
    ground_ = std::make_unique<Ground>(window_surface_ptr_, n_sheep, n_wolf);

    SDL_UpdateWindowSurface(window_ptr_);

    dog_ptr_ = std::make_shared<Dog>(window_surface_ptr_);
    ground_->add_animal(dog_ptr_);

    shepherd_ptr_ = std::make_shared<Shepherd>(window_surface_ptr_);
    ground_->add_human(shepherd_ptr_);
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
            // Ckick event used to move the sheperd's dog
            else if (window_event_.type == SDL_MOUSEBUTTONDOWN)
            {
                if (window_event_.button.button == SDL_BUTTON_LEFT)
                {
                    int x = window_event_.button.x;
                    int y = window_event_.button.y;
                    dog_ptr_->set_dog_target(x, y);
                }
            }
        }
        // Share the shepherd's position with the dog
        dog_ptr_->set_shepherd_position(shepherd_ptr_->point.x, shepherd_ptr_->point.y);
        
        handle_keyboard_input(shepherd_ptr_);
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
    if (SDL_BlitSurface(background_, NULL, window_surface_ptr_, NULL) < 0)
    {
        throw std::runtime_error("can't blit surface");
    }
}

SDL_Window *Application::create_window()
{
    // Initialize SDL window
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_QUIT;

    // Create a window, use frame_width and frame_height, frame_boundary
    SDL_Window *window_ptr = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                              frame_width, frame_height, flags);
    return window_ptr;
}

void Application::handle_keyboard_input(const std::shared_ptr<Shepherd> &shepherd_ptr)
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]) //Keyboard layout of SDL is only on QWERTY so we use WASD
    {
        shepherd_ptr->move(0, -3);
    }
    if (keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S])
    {
        shepherd_ptr->move(0, 3);
    }
    if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A])
    {
        shepherd_ptr->move(-3, 0);
    }
    if (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D])
    {
        shepherd_ptr->move(3, 0);
    }
}
