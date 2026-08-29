#include "pch.h"
#include "SpriteAnimRendererComponent.h"
#include "Engine.h"
#include "Renderer/TextureFrames.h"

namespace nu
{
	FACTORY_REGISTER(SpriteAnimRendererComponent)

	void SpriteAnimRendererComponent::Update(float dt)
	{
		m_frameTimer += dt;
		float frameTime = 1.0f / m_fps;
		// increase frame while frame timer is greater than frame time
		while (m_frameTimer >= frameTime) {
			m_frame++;
			if (m_loop) {
				m_frame %= m_textureFrames->GetTotalFrames();
			}
			else {
				m_frame = math::Clamp(0, m_textureFrames->GetTotalFrames() - 1, m_frame);
			}

			m_frameTimer -= frameTime;
		}
	}

	void SpriteAnimRendererComponent::Draw(const Renderer& renderer)
	{
		if (!m_textureFrames) return;
		auto transform = GetOwner()->GetTransform();
		renderer.DrawTexture(
			*m_textureFrames->GetTexture(),
			m_textureFrames->GetFrameRect(m_frame), 
			transform);
	}

	void SpriteAnimRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "fps", m_fps);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string texture_frames;
		JSON_READ_REQ(value, texture_frames);

		if (texture_frames.empty()) {
			std::cerr << "Could not load texture frames: " << texture_frames << std::endl;
		}
		else {
			m_textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
		}
	}
}
