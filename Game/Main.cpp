#include "Engine.h"

#include "SpaceGame/SpaceGame.h"

#include <iostream>
#include <vector>
#include <random>

using namespace nu;
using namespace std;

const float WIN_WIDTH = 1024.0f;
const float WIN_HEIGHT = 1080.0f;

int main()
{   
    nu::SetWorkingDirectory("assets/SpaceGame");

    // initialize the engine
    if (Engine::Get().Initialize(WIN_WIDTH, WIN_HEIGHT) == false) return 0;

    unique_ptr<SpaceGame> spaceGame = make_unique<SpaceGame>();

    spaceGame->Initialize();

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

        spaceGame->Update(dt);

        // get the current position & state of the mouse
        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        // ---------------
        // --- DRAWING ---
        // ---------------

        Engine::Get().GetRenderer().SetColour(0, 0, 0);
        Engine::Get().GetRenderer().Clear(); // Clear the renderer

        spaceGame->Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present(); // render the screen
    }

    spaceGame.reset();
    // shut down the program cleanly upon exiting
    Engine::Get().Shutdown();

    return 0;

}
