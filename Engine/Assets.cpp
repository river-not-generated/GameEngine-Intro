#include "pch.h"
#include "Assets.h"

using namespace nu;

namespace assets {
    Mesh playerBody(
        {
               { 6, 0 }, 
            { -4, -2 }, 
            { -2, 0 }, 
            { -4, 2 }, 
            { 6, 0 }, 
        },
        Colour{ 255, 255, 255 }
    );
    Mesh playerWing1(
        { 
            { 3, -1 }, 
            { -2, -3 },
            { 0, -3 },
            { 3, -1 } 
        },
        Colour{ 125, 125, 125 }
    );
    Mesh playerWing2(
        { 
            { 3, 1 },
            { -2, 3 },
            { 0, 3 },
            { 3, 1 } 
        },
        Colour{ 125, 125, 125 }
    );
    Mesh playerFlame(
        { 
            { -4, 1 },
            { -6, 0 },
            { -4, -1 }, 
            { -3, 0 },
            { -4, 1 } 
        },
        Colour{ 255, 200, 0 }
    );
    Model playerModel = std::vector<Mesh>{ playerBody, playerWing1, playerWing2, playerFlame };


    Mesh bulletMesh {
        {
            { -1, -1 },
            { 1, 0 },
            { -1, 1 },
            { -1, -1 },
        },
        Colour { 100, 225, 255 }
    };

    Model bulletModel{ std::vector<Mesh>{bulletMesh} };


    Mesh enemyMesh{
        {
            { 4, 0 },
            { -4, -6 },
            { -2, 0 },
            { -4, 6 },
            { 4, 0 },
            { 0, -3 },
            { 8, 0 },
            { 0, 3 },
        },
        Colour {255, 100, 0}
    };

    Model enemyModel{ std::vector<Mesh>{enemyMesh} };


    Mesh tripleDiamond{
        {
            { -10, 0 },
            { 0, -10 },
            { 10, 0 },
            { 0, 10 },
            { -10, 0 }
        },
        Colour {0, 230, 150}
    };

    Mesh bulletIcon{
        {
            { -5, 2 },
            { 0, -4 },
            { 5, 2 },
            { 0, 0 },
            { -5, 2 }
        },
        Colour {0, 230, 150}
    };

    Model tripleShotModel{ {tripleDiamond, bulletIcon} };

    Mesh heartDiamond{
    {
        { -10, 0 },
        { 0, -10 },
        { 10, 0 },
        { 0, 10 },
        { -10, 0 }
    },
    Colour {255, 100, 150}
    };

    Mesh heartIcon{
        {
            { 0, 7 },
            { -6, 0 },
            { -4, -4 },
            { -2, -4 },
            { 0, -2 },
            { 2, -4 },
            { 4, -4 },
            { 6, 0 },
            { 0, 7 }
        },
        Colour {255, 100, 150}
    };

    Model heartModel{ {heartDiamond, heartIcon} };
}