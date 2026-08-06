#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include "SpaceGame.h"

#include <iostream>
#include <vector>

using namespace nu;
using namespace std;

const float WIN_WIDTH = 1024.0f;
const float WIN_HEIGHT = 1080.0f;

class Object {
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { cout << "copy\n"; }
    Object& operator = (const Object& object) { cout << "assignment\n"; return *this; }
};

int main()
{
    std::cout << "=================== object =====================\n";
    {
        Object objectA;
        Object objectB(objectA);
        Object objectC;
        objectC = objectA;
    }

    std::cout << "=============== raw pointers =================\n";
    {
        Object* objectA = new Object();
        std::cout << objectA << endl;
        Object* objectB = new Object(*objectA);
        std::cout << objectB << endl;
        Object* objectC = nullptr;
        objectC = objectA;
        std::cout << objectC << std::endl;

        delete objectA;
        delete objectB;
    }

    std::cout << "=============== smart pointers =================\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectB.get() << std::endl;

        objectB.reset();
    }

    std::cout << "=============== shared pointers =================\n";
    shared_ptr<Object> objectC;
    {
        shared_ptr<Object> objectA = std::make_shared<Object>();
        std::cout << objectA.get() << std::endl;
        std::cout << objectA.use_count() << std::endl;
        auto objectB = objectA;
        std::cout << objectB.get() << std::endl;
        std::cout << objectB.use_count() << std::endl;
        objectC = objectA;
        std::cout << objectC.get() << std::endl;
        std::cout << objectC.use_count() << std::endl;
    }
    std::cout << objectC.use_count() << std::endl;



    // initialize the engine
    if (Engine::Get().Initialize(WIN_WIDTH, WIN_HEIGHT) == false) return 0;
    nu::SetWorkingDirectory("assets");

    SpaceGame game;

    game.Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load("textures/player.png", Engine::Get().GetRenderer() );


    // -----------------
    // --- MAIN LOOP ---
    // -----------------

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();

        game.Update(dt);

        // get the current position & state of the mouse
        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        // ---------------
        // --- DRAWING ---
        // ---------------

        Engine::Get().GetRenderer().SetColour(0, 0, 0);
        Engine::Get().GetRenderer().Clear(); // Clear the renderer

        game.Draw(Engine::Get().GetRenderer());


        Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("textures/player.png", Engine::Get().GetRenderer()), 30, 30, 60);


        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present(); // render the screen
    }

    // shut down the program cleanly upon exiting
    Engine::Get().Shutdown();

    return 0;

}
