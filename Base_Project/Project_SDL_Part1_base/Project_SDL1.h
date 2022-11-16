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
constexpr char path_img_sheep[] = "../media/sheep.png";
constexpr char path_img_wolf[] = "../media/wolf.png";
constexpr char path_img_grass[] = "../media/grass.png"; 


void init();                            // Helper function to initialize SDL

class animal 
{
private:
    SDL_Surface* window_surface_ptr_; 
    // Ptr to the surface on which we want the
    // Animal to be drawn, also non-owning

    SDL_Surface* image_ptr_; 
    // The texture of the Sheep (the loaded image), use load_surface_for

    // TODO: Attribute(s) to define its position
    //

public:
    // TODO: The constructor has to load the sdl_surface that corresponds to 
    // the texture
    animal(const std::string& file_path, SDL_Surface* window_surface_ptr, int animal_height, int animal_width);
    ~animal();
//     TODO: Use the destructor to release memory and "clean up behind you"

    void draw();
    // TODO: Draw the animal on the screen <-> window_surface_ptr.
    // Note that this function is not virtual, it does not depend
    // on the static type of the instance

     virtual void move(){};
    // TODO: Animals move around, but in a different fashion depending on which
    // type of animal

    unsigned getX() const;

    unsigned getY() const;

protected:
    int _x;
    int _y;

    int _h_size;
    int _w_size;

    unsigned time_to_change;

    unsigned _x_dir;
    unsigned _y_dir;

    unsigned speed;

    void get_next_pos();
};

// Insert here:
// class Sheep, derived from animal
class Sheep : public animal
{

    public:
        Sheep(SDL_Surface *window_surface_ptr);

        virtual void move() override;

    // TODO
    // Ctor
    // Dtor
    // 
    // implement functions that are purely virtual in base class
};

// Insert here:
// class Wolf, derived from animal. Use only Sheep at first.
// Once the application works for Sheep you can add the wolves
class Wolf : public animal
{

    public:
        Wolf(SDL_Surface *window_surface_ptr);

        virtual void move() override;

    // Astuce : le faire se déplacer à un point aléatoire à la place de random
    // TODO
    // Ctor
    // Dtor
    //
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
    unsigned _nb_sheep;
    unsigned _nb_wolf;
    std::vector<std::shared_ptr<animal>> animals;

public:
    // TODO: Ctor
    ground(SDL_Surface* window_surface_ptr, unsigned n_sheep, unsigned n_wolf);

    // TODO: Dtor, again for clean up (if necessary)
    ~ground(){}; 

    // TODO: Add an animal
    void add_animal(const std::shared_ptr<animal>& animal);

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
    SDL_Surface *background_;

    // Other attributes here, for example an instance of ground
    // Instance of ground
    std::unique_ptr<ground> ground_;
    void print_background();
public:
    application(unsigned n_sheep, unsigned n_wolf); // Ctor
    ~application(); 
                                    // Dtor

    /*
       Main loop of the application. This ensures that the screen is updated
       at the correct rate. See SDL_GetTicks() and SDL_Delay() to enforce a
       duration the application should terminate after 'period' seconds
       */
    int loop(unsigned period); 
};
