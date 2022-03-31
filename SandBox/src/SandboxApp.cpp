#include "melisma.h"

using namespace melisma;

class ExampleLayer : public Layer {
public:
	virtual void OnAttach() override {

		auto viewport = Application::Instance->GetWindow()->GetViewport();

		m_PlayerPos = glm::vec2(508.0f);
		m_Camera = CreateScope<ScreenCoordCamera>(viewport, m_PlayerPos, 1.0f);
		Renderer2D::SetViewport(viewport);
	}

	virtual void OnUpdate(const DeltaTime &dt) override {

		const float player_base_speed = 200.0f;
		float player_speed = player_base_speed * (!IsKeyPressed(KeyCode::LeftShift) ? 1.0f : 0.5f);

		if (IsKeyPressed(KeyCode::Right)) m_PlayerPos.x += player_speed * dt;
		if (IsKeyPressed(KeyCode::Left)) m_PlayerPos.x  -= player_speed * dt;
		if (IsKeyPressed(KeyCode::Down)) m_PlayerPos.y  -= player_speed * dt;
		if (IsKeyPressed(KeyCode::Up)) m_PlayerPos.y    += player_speed * dt;

		const float attraction = .015f;
		float distance = glm::length(m_Camera->Position - m_PlayerPos);

		if (distance > 50.0f * dt)
		{
			m_Camera->Position += (m_PlayerPos - m_Camera->Position) * (distance + 50.0f) * attraction * dt;
		}
		else {
			m_Camera->Position = m_PlayerPos;
		}
	}

	virtual void OnRender() {
		Renderer2D::Clear(glm::vec4(.2f));
		Renderer2D::BeginScene((Camera&) *m_Camera);

		for(int i = 0; i < 50; i++)
			for (int j = 0; j < 50; j++)
				Renderer2D::DrawQuad(
          glm::vec2(20 * i, 20 * j), 
          glm::vec2(16, 16), 
          glm::vec4(i / 50.0f, 0.5f, j / 50.0f, 1.0f));
		
		const int player_size = 200.0f;
		Renderer2D::DrawQuad(
			m_PlayerPos - glm::vec2(player_size / 2),
			glm::vec2(player_size),
			glm::vec4(0.2f, 0.6f, 0.8f, 1.0f));

		Renderer2D::EndScene();
	}

	virtual bool OnWindowResize(WindowResizeEvent &e) override {

		auto viewport = Application::Instance->GetWindow()->GetViewport();

		m_Camera->Viewport = viewport;
		Renderer2D::SetViewport(viewport);

		return true;
	}

	virtual bool OnKeyPressed(KeyPressedEvent &e) override {
		if (e.GetKeyCode() == KeyCode::Escape)
		{
			WindowCloseEvent e;
			Application::Instance->OnEvent(e);

			return true;
		}
		
		return false;
	}

private:
	Scope<ScreenCoordCamera> m_Camera;
	glm::vec2 m_PlayerPos;
};

class SandboxApp : public Application {
public:
	using Application::Application;

	virtual void Init() override {
		m_Window->SetSize(1000, 1000);
		PushLayerTop(CreateRef<ExampleLayer>());
	}
};

Application *CreateApplication() {
	return new SandboxApp;
}