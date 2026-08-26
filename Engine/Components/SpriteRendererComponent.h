#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
#include "Renderer/Texture.h"

namespace nu
{
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)

		void Draw(const class Renderer& renderer) override;

		virtual void Read(const json::value_t& value);

	protected:
		res_t<Texture> m_texture;

	};
}