#include "melisma.h"

using namespace melisma;

#define SCR_WIDTH 800
#define SCR_HEIGHT 800

#include <vector>

class RenderLayer : public Layer {
public:
	virtual void OnAttach() override {

		// Load textures
		
		TextureSpecification spec;
		spec.colorSpace = ColorSpace::RGB;

		m_Textures.push_back(CreateRef<Texture>("textures/erling.jpg",  spec));
		m_Textures.push_back(CreateRef<Texture>("textures/matisse.jpg", spec));
		spec.colorSpace = ColorSpace::RGBA;
		m_Textures.push_back(CreateRef<Texture>("textures/Tree.png", spec));
		m_Textures.push_back(CreateRef<Texture>("textures/map.png", spec));

		m_ActiveTexture = m_Textures.begin();

		// Init viewport
		Renderer2D::SetViewport(Viewport(0, 0, SCR_WIDTH, SCR_HEIGHT));
		m_Camera = Camera(glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, -1.0f, 100.0f));

		m_Scale = 1.0f;
	}


	virtual void OnUpdate(const DeltaTime&) override {

		// COnfigure docking
		auto right_x = Application::Instance->GetWindow()->GetWidth()  - m_Scale * (*m_ActiveTexture)->Width();
		auto top_y   = Application::Instance->GetWindow()->GetHeight() - m_Scale * (*m_ActiveTexture)->Height();

		// Renderer textures
		Renderer2D::Clear(glm::vec4(0.3f, 0.2f, 0.2f, 1.0f));
		Renderer2D::BeginScene(m_Camera);
		Renderer2D::DrawTexturedQuad({ 0,		0		}, *m_ActiveTexture, m_Scale);
		Renderer2D::DrawTexturedQuad({ right_x, 0		}, *m_ActiveTexture, m_Scale);
		Renderer2D::DrawTexturedQuad({ 0,		top_y	}, *m_ActiveTexture, m_Scale);
		Renderer2D::DrawTexturedQuad({ right_x, top_y	}, *m_ActiveTexture, m_Scale);
		Renderer2D::EndScene();

		// Poll input
		if (IsKeyPressed(KeyCode::Up)) m_Scale *= 1.02f;
		if (IsKeyPressed(KeyCode::Down))  m_Scale /= 1.02f;
	}


	virtual bool OnWindowResize(WindowResizeEvent &e) override {

		// Update viewport
		Renderer2D::SetViewport(Viewport(0, 0, e.Width, e.Height));
		m_Camera = Camera(glm::ortho(0.0f, (float)e.Width, 0.0f, (float)e.Height, -1.0f, 100.0f));

		return false;
	}


	virtual bool OnKeyPressed(KeyPressedEvent &e) override {
		mlLog("Key pressed: " << (int)e.GetKeyCode());

		// Exit
		if (e.GetKeyCode() == KeyCode::Escape) {
			WindowCloseEvent we;
			Application::Instance->OnEvent((Event&)we);
		}

		// Cycle through textures
		if (e.GetKeyCode() == KeyCode::Space) {
			m_ActiveTexture++;

			if (m_ActiveTexture == m_Textures.end())
				m_ActiveTexture = m_Textures.begin();
		}

		return false;
	}


private:
	std::vector<Ref<Texture>> m_Textures;
	std::vector<Ref<Texture>>::const_iterator m_ActiveTexture;

	Camera m_Camera;
	float m_Scale;
};




class SandboxApp : public Application {
public:
	SandboxApp() : Application() {
		PushLayerTop(Ref<Layer>(new RenderLayer));

		m_Window->Maximize();
	}
};




Application *CreateApplication() {
	return new SandboxApp;
}