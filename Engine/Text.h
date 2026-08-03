#pragma once
#include "Font.h"
#include "Vector3.h"

struct SDL_Texture;

namespace nu
{
	class Renderer;

	class Text {
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const Colour& color);
		void Draw(const Renderer& renderer, float x, float y) const;

	private:
		Font* m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};

}