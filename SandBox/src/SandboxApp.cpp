#include "melisma.h"

using namespace melisma;

#define SCR_WIDTH 800
#define SCR_HEIGHT 800

#include <vector>
#include <format>
#include <algorithm>


class ParalaxLayer : public Layer {
public:
	virtual void OnAttach() override {

		// Load textures
		TextureSpecification spec;
		spec.colorSpace = ColorSpace::RGBA;

		for (int i = 11; i >= 0; i--) {
			auto path = std::format("textures/forest/Layer{:02d}.png", i);

			m_Textures.push_back(CreateRef<Texture>(path.c_str(), spec));
		}

		m_Hpos = 0;
		m_Hspeed = 0;
		m_Dir = 1;

		{
			WindowResizeEvent winresev(SCR_WIDTH, SCR_HEIGHT);
			OnWindowResize(winresev);
		}
	}


	virtual void OnUpdate(const DeltaTime&) override {

		const float speed = 5.0f;
		if (IsKeyPressed(KeyCode::Right)) { 
			m_Hspeed = speed; m_Dir = -1; 
		}
		if (IsKeyPressed(KeyCode::Left)) {
			m_Hspeed = speed; m_Dir = 1;
		}
		
		m_Hpos += m_Hspeed * m_Dir;
		const float damping = .1f;
		m_Hspeed -= damping;
		m_Hspeed = m_Hspeed < 0 ? 0 : m_Hspeed;

		float w = Application::Instance->GetWindow()->GetWidth();
		float h = Application::Instance->GetWindow()->GetHeight();
		float size = std::max(h / m_Textures[0]->Height(), w / m_Textures[0]->Width());

		Renderer2D::Clear({ 1.0f, 1.0f, 1.0f, 1.0f });
		Renderer2D::BeginScene(m_Camera);
		
		for (int i = 0; i < m_Textures.size(); i++) {
			float offset = size * m_Hpos / (12 - i);
			Renderer2D::DrawTexturedQuad(glm::vec2(offset - size * m_Textures[0]->Width(), 0), m_Textures[i], size);
			Renderer2D::DrawTexturedQuad(glm::vec2(offset, 0), m_Textures[i], size);
			Renderer2D::DrawTexturedQuad(glm::vec2(offset + size * m_Textures[0]->Width(), 0), m_Textures[i], size);
		}
		Renderer2D::EndScene();
	}

	virtual bool OnWindowResize(WindowResizeEvent &e) override {
		Renderer2D::SetViewport(Viewport(0, 0, e.Width, e.Height));
		m_Camera = Camera(glm::ortho(0.0f, (float)e.Width, 0.0f, (float)e.Height, -1.0f, 10.0f));

		return true;
	}

	virtual bool OnKeyPressed(KeyPressedEvent &e) override {
		if (e.GetKeyCode() == KeyCode::Escape) {
			WindowCloseEvent wce;
			Application::Instance->OnEvent(wce);
		}

		return true;
	}


private:
	std::vector<Ref<Texture>> m_Textures;
	Camera m_Camera;
	float m_Hpos;
	float m_Hspeed;
	int m_Dir;
};




class SandboxApp : public Application {
public:
	SandboxApp() : Application() {
		PushLayerTop(Ref<Layer>(new ParalaxLayer));
	}
};




Application *CreateApplication() {
	return new SandboxApp;
}