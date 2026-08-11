#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <random>

using namespace nu;
using namespace std;

const float WIN_WIDTH = 1024.0f;
const float WIN_HEIGHT = 1080.0f;

int main()
{   
    nu::SetWorkingDirectory("assets");

    Factory::Instance().Register<Actor>("Actor");
    auto actor = Factory::Instance().Create("Actor");

    cout << actor->IsActive() << endl;


    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("data/data.json", document))
        {
            // read the age data (int) from the json
            int age;
            JSON_READ(document, age);
            // show the age data
            std::cout << age << std::endl;
        }

        // read/show the data from the json file
        std::string name;
        int age;
        float speed;
        bool isAwake;
        Vector2 position;
        Vector3 colour;

        // read the json data
        JSON_READ(document, name);
        JSON_READ(document, age);
        JSON_READ(document, speed);
        JSON_READ(document, isAwake);
        JSON_READ(document, position);
        JSON_READ(document, colour);

        // show the data
        std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
        std::cout << position.x << " " << position.y << std::endl;
        std::cout << colour.r << " " << colour.g << " " << colour.b << " " << std::endl;

    }
    return 0;

    // initialize the engine
    if (Engine::Get().Initialize(WIN_WIDTH, WIN_HEIGHT) == false) return 0;

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

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present(); // render the screen
    }

    // shut down the program cleanly upon exiting
    Engine::Get().Shutdown();

    return 0;

}
