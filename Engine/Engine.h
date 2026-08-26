#pragma once

#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/MathUtils.h"
#include "StringUtils.h"
#include "Math/Transform.h"

#include "Text.h"
#include "Texture.h"

#include "Factory.h"
#include "ResourceManager.h"

#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "Game.h"
#include "ParticleSystem.h"
#include "Physics/Physics.h"
#include "Json.h"

#include "Actor.h"
#include "Mesh.h"
#include "Scene.h"
#include "Audio/Audio.h"
#include "File.h"

namespace nu
{
	class Engine {
		public:
			static Engine& Get() { static Engine engine; return engine; }

			bool Initialize(float width, float height);
			void Shutdown();

			void Update();

			Input& GetInput() { return m_input; }
			Renderer& GetRenderer() { return m_renderer; }
			Time& GetTime() { return m_time; }
			Audio& GetAudio() { return m_audio; }
			ParticleSystem& GetPS() { return m_particleSystem; }
			Physics& GetPhysics() { return m_physics; }


			Engine(const Engine&) = delete;
			Engine& operator = (const Engine&) = delete;

		private:
			Engine() = default;

		private:
			Input m_input;
			Renderer m_renderer;
			Time m_time;
			Audio m_audio;
			ParticleSystem m_particleSystem;
			Physics m_physics;
	};
}

void fnEngine();