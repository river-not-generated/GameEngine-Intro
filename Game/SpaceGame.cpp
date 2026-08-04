#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Powerup.h"
#include "Assets.h"

using namespace nu;

bool SpaceGame::Initialize() {
    Game::Initialize();

    m_scene = new Scene();
    m_scene->SetGame(this);

    // i'm tired of typing out the whole thing
    auto renderer = Engine::Get().GetRenderer();

    // AUDIO
    Engine::Get().GetAudio().AddSound("bell", "audio/cowbell.wav");
    Engine::Get().GetAudio().PlaySound("bell");
    Engine::Get().GetAudio().AddSound("hurt", "audio/sndHurt.mp3");
    Engine::Get().GetAudio().AddSound("death", "audio/sndDeath.mp3");
    Engine::Get().GetAudio().AddSound("fire", "audio/sndFire.mp3");
    Engine::Get().GetAudio().AddSound("powerup", "audio/sndPowerupPickup.mp3");
    Engine::Get().GetAudio().AddSound("kill", "audio/sndAsteroidHit.mp3");
    Engine::Get().GetAudio().AddSound("blip", "audio/sndBlip.mp3");
    Engine::Get().GetAudio().AddSound("thrust", "audio/sndThrust.mp3");

    // FONTS
    m_fonts["big"] = new Font();
    m_fonts["big"]->Load("fonts/bytesized.ttf", 64);
    m_fonts["regular"] = new Font();
    m_fonts["regular"]->Load("fonts/tiny5.ttf", 32);
    m_fonts["medium"] = new Font();
    m_fonts["medium"]->Load("fonts/tiny5.ttf", 48);

    // TITLE SCREEN TEXT
    m_text["title"] = new Text(m_fonts["big"]);
    m_text["title"]->Create(renderer, "Another Space Game", Colour{255,255,255});
    m_text["subtitle"] = new Text(m_fonts["regular"]);
    m_text["subtitle"]->Create(renderer, "The objectively worse sequel to the gamemaker one", Colour{ 255,255,255 });
    m_text["start"] = new Text(m_fonts["medium"]);
    m_text["start"]->Create(renderer, "Press enter to continue", Colour{ 255,255,255 });

    // GAME UI
    m_text["score"] = new Text(m_fonts["regular"]);
    m_text["score"]->Create(renderer, "Score: " + std::to_string(m_score), Colour{ 255,255,255 });
    m_text["lives"] = new Text(m_fonts["regular"]);
    m_text["lives"]->Create(renderer, "Lives: " + std::to_string(m_lives), Colour{ 255,255,255 });
    m_text["fire"] = new Text(m_fonts["regular"]);
    m_text["fire"]->Create(renderer, "Space to fire", Colour{ 255,255,255 });
    m_text["dash"] = new Text(m_fonts["regular"]);
    m_text["dash"]->Create(renderer, "Left shift to dash", Colour{ 255,255,255 });


    // GAME OVER SCREEN TEXT
    m_text["gameover"] = new Text(m_fonts["big"]);
    m_text["gameover"]->Create(Engine::Get().GetRenderer(), "Game Over", Colour{ 255,255,255 });
    m_text["finalscore"] = new Text(m_fonts["regular"]);
    m_text["finalscore"]->Create(renderer, "Final Score: " + std::to_string(m_score), Colour{ 255,255,255 });

    return true;
}

void SpaceGame::Update(float dt) {
    nu::Particle star;
    switch (m_gamestate) {
        case SpaceGame::GameState::Title:
            // make stars rain down from the top
            star.position = { RandomFloat(0, Engine::Get().GetRenderer().GetWindowWidth()), 0.0f };
            star.colour = { 255, 255, 255 };
            star.lifespan = 5.0f;
            star.velocity = { 0.0f, nu::RandomFloat(300.0f, 550.0f) };

            nu::Engine::Get().GetPS().AddParticle(star);

            if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_RETURN)) {
                m_gamestate = GameState::StartGame;
            }
            break;
        case SpaceGame::GameState::StartGame:
            m_score = 0;
            m_lives = 3;
            m_spawnMod = 1.0f;
            m_killCount = 0;
            m_gamestate = GameState::StartLevel;
            m_stateTimer = 0.0f;
            break;
        case SpaceGame::GameState::StartLevel:
            m_stateTimer -= dt;
            if (m_stateTimer <= 0) {
                m_scene->RemoveAllActors();
                m_spawnTime = 1.0f;
                m_powerupSpawnTime = 5.0f;
                SpawnPlayer();
                Engine::Get().GetAudio().PlaySound("blip");
                m_gamestate = GameState::Game;
            }
            break;
        case SpaceGame::GameState::Game:
            m_spawnTime -= dt;
            if (m_spawnTime <= 0) {
                m_spawnTime = nu::RandomFloat(3.0f, 4.0f) * m_spawnMod;
                SpawnEnemy();
            }
            m_powerupSpawnTime -= dt;
            if (m_powerupSpawnTime <= 0) {
                m_powerupSpawnTime = nu::RandomFloat(12.5f, 15.0f);
                SpawnPowerup();
            }
            break;
        case SpaceGame::GameState::EndLevel:
            break;
        case SpaceGame::GameState::GameOver:
            if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_RETURN)) {
                m_scene->RemoveAllActors();
                m_gamestate = GameState::Title;
            }
            break;
        default:
            break;
    }

    Game::Update(dt);
}

void SpaceGame::Draw(nu::Renderer& renderer) {
    Game::Draw(renderer);
    switch (m_gamestate) {
        case SpaceGame::GameState::Title:
            m_text["title"]->Draw(renderer, 225, 400);
            m_text["subtitle"]->Draw(renderer, 150, 500);
            m_text["start"]->Draw(renderer, 275, 600);
            break;
        case SpaceGame::GameState::StartGame:
        case SpaceGame::GameState::StartLevel:
        case SpaceGame::GameState::Game:
            m_text["score"]->Create(renderer, "Score: " + std::to_string(m_score), Colour{ 255,255,255 });
            m_text["score"]->Draw(renderer, 50, 50);
            m_text["lives"]->Create(renderer, "Lives: " + std::to_string(m_lives), Colour{ 255,255,255 });
            m_text["lives"]->Draw(renderer, Engine::Get().GetRenderer().GetWindowWidth() - 150, 50);
            m_text["fire"]->Draw(renderer, 50, Engine::Get().GetRenderer().GetWindowHeight() - 100);
            m_text["dash"]->Draw(renderer, 50, Engine::Get().GetRenderer().GetWindowHeight() - 50);
            break;
        case SpaceGame::GameState::EndLevel:
            break;
        case SpaceGame::GameState::GameOver:
            m_text["gameover"]->Draw(renderer, 375, 400);
            m_text["finalscore"]->Create(renderer, "High Score: " + std::to_string(m_highScore), Colour{ 255,255,255 });
            m_text["finalscore"]->Draw(renderer, 400, 500);
            m_text["start"]->Draw(renderer, 275, 600);
            
            break;
        default:
            break;
    }
}

void SpaceGame::SpawnPlayer() {
    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.tag = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.transform = Transform{ Vector2{ Engine::Get().GetRenderer().GetWindowWidth() / 2, Engine::Get().GetRenderer().GetWindowHeight() / 2}, 0.0f, 5.0f };
    playerDesc.velocity = { 0.0f, 0.0f };
    playerDesc.speed = 800.0f;
    playerDesc.damping = 0.7f;

    std::unique_ptr<Player> player = std::make_unique<Player>(playerDesc);
    m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy() {
    float winWidth = Engine::Get().GetRenderer().GetWindowWidth();
    float winHeight = Engine::Get().GetRenderer().GetWindowHeight();
    EnemyDesc enemyDesc;
    enemyDesc.name = "Enemy";
    enemyDesc.tag = "Enemy";
    enemyDesc.model = assets::enemyModel;
    // only spawn enemies on the edges of the screen to reduce the risk of spawning on top of the player
    enemyDesc.transform = Transform{ 
        Vector2{ RandomInt(0, 1) == 0 ? RandomFloat(0, winWidth / 4.0f) : RandomFloat(winWidth * (0.5f), winWidth)
        , RandomInt(0, 1) == 0 ? RandomFloat(0, winHeight / 4.0f) : RandomFloat(winHeight * (0.75f), winHeight), }
        , 0.0f, 5.0f};
    enemyDesc.velocity = { 0.0f, 0.0f };
    enemyDesc.speed = 600.0f;
    enemyDesc.damping = 0.5f;

    std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(enemyDesc);
    m_scene->AddActor(std::move(enemy));
}

void SpaceGame::SpawnPowerup() {
    float winWidth = Engine::Get().GetRenderer().GetWindowWidth();
    float winHeight = Engine::Get().GetRenderer().GetWindowHeight();
    PowerupDesc powerupDesc;
    powerupDesc.name = "Powerup";
    powerupDesc.transform = Transform{ Vector2{RandomFloat(0, winWidth), RandomFloat(0, winHeight)}, 0.0f, 3.0f };
    powerupDesc.velocity = { 0.0f, 0.0f };

    int num = RandomInt(0, 1);
    switch (num) {
    case 0:
        powerupDesc.tag = "TripleShot";
        powerupDesc.model = assets::tripleShotModel;
        break;
    case 1:
        powerupDesc.tag = "Heart";
        powerupDesc.model = assets::heartModel;
        break;
    default:
        powerupDesc.tag = "TripleShot";
        powerupDesc.model = assets::tripleShotModel;
        break;
    }


    std::unique_ptr<Powerup> powerup = std::make_unique<Powerup>(powerupDesc);
    m_scene->AddActor(std::move(powerup));
}

void SpaceGame::OnPlayerDead() {
    m_lives -= 1;
    if (m_lives == 0) {
        m_gamestate = GameState::GameOver;
        Engine::Get().GetAudio().PlaySound("death");
        m_highScore = std::max(m_highScore, m_score);
    }
    else {
        m_gamestate = GameState::StartLevel;
        Engine::Get().GetAudio().PlaySound("hurt");
    }

    m_stateTimer = 3.0f;
}
