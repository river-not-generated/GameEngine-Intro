#pragma once

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_image/SDL_image.h"

namespace nu
{
	class Renderer {
	public:
		bool Initialize(const char* name, float width, float height, bool fullscreen = false);

		void Clear();
		void Present();

		float GetWindowWidth() { return m_width; }
		float GetWindowHeight() { return m_height; }

		void SetColour(float r, float g, float b, float a = 255.0f) const;
		void SetColour(const SDL_Color& colour) const;
		void SetColourRandom() const;

		void DrawPoint(float x, float y) const;
		void DrawFillRect(float x, float y, float width, float height) const;
		void DrawFillRect(const SDL_FRect* rect) const;
		void DrawRect(float x, float y, float width, float height) const;
		void DrawRect(const SDL_FRect* rect) const;
		void DrawLine(float x1, float y1, float x2, float y2) const;

		void DrawModel(const class Model& model, const struct Transform& trans) const;

		void DrawTexture(class Texture* texture, float x, float y);

		void DrawDebugText(float x, float y, const char* text) const;

		void Delay(int ms);

		void Shutdown();

		friend class Text;
		friend class Texture;

	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		float m_width = 1024.0f;
		float m_height = 1080.0f;
	};
};