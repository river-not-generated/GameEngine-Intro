#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Resources/ResourceManager.h"
#include <map>

class PlatformerGame : public nu::Game
{
public:
	enum class GameState {
		Title
		, StartGame
		, StartLevel
		, Game
		, EndLevel
		, GameOver
	};

public:
	PlatformerGame() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer) override;

private:


private:
	int m_score = 0;
	int m_highScore = 0;
	int m_lives = 0;
	int m_killCount = 0;
	float m_spawnMod = 1.0f;
	float m_spawnTime = 0.0f;
	float m_stateTimer = 0.0f;
	float m_powerupSpawnTime = 0.0f;

	std::map<std::string, nu::res_t<nu::Font>> m_fonts;
	std::map<std::string, nu::Text*> m_text;

	GameState m_gamestate = GameState::Title;
};