#include "melisma.h"

using namespace melisma;

#include <vector>
#include <filesystem>
#include <format>

class ExampleLayer : public Layer {
public:
	virtual void OnAttach() override {

		// Texture specification
		TextureSpecification tspec;
		tspec.hTiles = 4;
		tspec.vTiles = 4;
		m_Texture = CreateRef<Texture>("textures/map.jpg", tspec);

		m_UV = 0;

		CalculateView(
			Application::Instance->GetWindow()->GetWidth(),
			Application::Instance->GetWindow()->GetHeight());
	}

	virtual void OnRender() override {
		Renderer2D::Clear(glm::vec4(0.2f));

		Renderer2D::BeginScene(m_Camera);
		Renderer2D::DrawTexturedQuad(m_ImagePos, m_Texture, m_ImageSize, m_UV % 4, m_UV / 4);
		Renderer2D::EndScene();
	}

	virtual bool OnWindowResize(WindowResizeEvent &e) {
		CalculateView(e.Width, e.Height);
		mlLog("WindowResizeEvent: " << e.Width << ", " << e.Height);
		return false;
	}

	virtual bool OnKeyPressed(KeyPressedEvent &e) override {

		if (e.IsRepeated()) return false;

		switch (e.GetKeyCode()) {
		case KeyCode::Right:
			m_UV++;
			break;

		case KeyCode::Left:
			m_UV--;
			break;
		}

		CalculateView(
			Application::Instance->GetWindow()->GetWidth(),
			Application::Instance->GetWindow()->GetHeight());

		return true;
	}

	void CalculateView(int window_width, int window_height) {
		float x_ratio = window_width / static_cast<float>(m_Texture->Width());
		float y_ratio = window_height / static_cast<float>(m_Texture->Height());
		
		if (x_ratio > y_ratio) {
			m_ImageSize = y_ratio;
			m_ImagePos = glm::vec2(.5f * (window_width - m_ImageSize * m_Texture->Width()), 0);
		}
		else {
			m_ImageSize = x_ratio;
			m_ImagePos = glm::vec2(0, .5f * (window_height - m_ImageSize * m_Texture->Height()));
		}

		Renderer2D::SetViewport(Viewport(0, 0, window_width, window_height));
		m_Camera = Camera(glm::ortho(0.0f, (float)window_width, 0.0f, (float)window_height, -1.0f, 10.0f));
	}

private:
	glm::vec2 m_ImagePos;
	float m_ImageSize;
	int m_UV;
	Ref<Texture> m_Texture;
	Camera m_Camera;
};

class SandboxApp : public Application {
public:
	using Application::Application;

	virtual void Init() override {
		PushLayerTop(CreateRef<ExampleLayer>());
	}
};

Application *CreateApplication() {
	return new SandboxApp;
}