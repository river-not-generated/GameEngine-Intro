#pragma once

#include "Components/RendererComponent.h"
#include "ResourceManager.h"

namespace nu
{
	class SpriteAnimRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteAnimRendererComponent)

		void Update(float dt) override;
		void Draw(const Renderer& renderer) override;

		void Read(const json::value_t& value) override;

	private:
		float m_fps = 1.0f;
		float m_frameTimer = 0.0f;

		bool m_loop = true;
		int m_frame = 0;
		res_t<class TextureFrames> m_textureFrames;

	};
}