// SDL_Test.h: Include file for standard system include files,
// or project specific include files.

/* TODO List :
   -> Comment créer une fenetre (SDL_CreateWindow)
   -> Comment récuperer la surface sur laquelle vous affichez des images  
   (SDL_GetWindowSurface)
   -> Comment charger une image (IMG_Load), (vous pouvez ignorer la fonction 
   "load_image_for" pour le moment)
   -> Comment afficher (SDL_BlitSurface)
   -> Définir une région (SDL_Rect)
   -> Comment fermer et assurer qu'il n'y a pas des fuites de mémoire 
   (Je vous laisse chercher)

   Layout du code:
   -> Quelle variable membre dans quelle classe
   -> Quel type de donnés
   -> Comment stocker une nombre inconnue des animaux 
   (animaux!, on stocke de manière indifferent les moutons ET les loups)
   -> Comment concevoir la boucle d'affichage, quelle sont les valeurs 
   "raissonable" pour la vitesse de déplacement
   -> Comment empecher qu'un animal "sort" du fenetre 
   (vous pouvez le faire "rebondir" ou eviter la frontière de votre fenetre)
*/

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

// Definitions
constexpr double frame_rate = 60.0;             // Refresh rate
constexpr double frame_time = 1. / frame_rate;  // Time per frame
constexpr unsigned frame_width = 1400;          // Width of window in pixel
constexpr unsigned frame_height = 900;          // Height of window in pixel
constexpr unsigned frame_boundary = 100;        // Minimal distance of animals 
                                                // to the border of the screen


void init();                            // Helper function to initialize SDL

class animal 
{
private:
    SDL_Surface* window_surface_ptr_; 
    // Ptr to the surface on which we want the
    // Animal to be drawn, also non-owning

    SDL_Surface* image_ptr_; 
    // The texture of the sheep (the loaded image), use load_surface_for

    // TODO: Attribute(s) to define its position

public:
    // TODO: The constructor has to load the sdl_surface that corresponds to 
    // the texture
    animal(const std::string& file_path, SDL_Surface* window_surface_ptr);
    ~animal();
//     TODO: Use the destructor to release memory and "clean up behind you"

    void draw(){}; 
    // TODO: Draw the animal on the screen <-> window_surface_ptr.
    // Note that this function is not virtual, it does not depend
    // on the static type of the instance

    // virtual void move(SDL_Surface *window_surface_ptr){} = 0;
    // TODO: Animals move around, but in a different fashion depending on which
    // type of animal

    unsigned getX() const;

    unsigned getY() const;

protected:
    unsigned _x;
    unsigned _y;

    unsigned _h_size;
    unsigned _w_size;

};

// Insert here:
// class sheep, derived from animal
class sheep : public animal 
{
    unsigned const speed = 20;

    public:
        sheep(SDL_Surface *window_surface_ptr);

        // virtual void move(SDL_Surface *window_surface_ptr) override;

    // TODO
    // Ctor
    // Dtor
    // implement functions that are purely virtual in base class
};

// Insert here:
// class wolf, derived from animal. Use only sheep at first.
// Once the application works for sheep you can add the wolves
class wolf : public animal
{
    unsigned speed = 20;

    public:
        wolf(SDL_Surface *window_surface_ptr);

        // virtual void move(SDL_Surface *window_surface_ptr) override;

    // Astuce : le faire se déplacer à un point aléatoire à la place de random
    // TODO
    // Ctor
    // Dtor
    // implement functions that are purely virtual in base class
};

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground
{
private:
    // Attention, NON-OWNING ptr, again to the screen
    SDL_Surface* window_surface_ptr_;

    // Attribute to store all the wolves and sheeps
    // TODO

public:
    // TODO: Ctor
    ground(SDL_Surface* window_surface_ptr); 

    // TODO: Dtor, again for clean up (if necessary)
    ~ground(){}; 

    // TODO: Add an animal
    //void add_animal(some argument here);

    // TODO: "refresh the screen": Move animals and draw them
    // Possibly other methods, depends on your implementation
    void update();
};

// The application class, which is in charge of generating the window
class application {
private:
    // The following are OWNING ptrs
    SDL_Window* window_ptr_;
    SDL_Surface* window_surface_ptr_;
    SDL_Event window_event_;

    // Other attributes here, for example an instance of ground

    // Instance of ground
    ground ground_;
public:
    application(unsigned n_sheep, unsigned n_wolf); // Ctor
    ~application();                                 // Dtor

    /*
       Main loop of the application. This ensures that the screen is updated
       at the correct rate. See SDL_GetTicks() and SDL_Delay() to enforce a
       duration the application should terminate after 'period' seconds
       */
    int loop(unsigned period); 
};
