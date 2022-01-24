#include "melisma.h"

using namespace melisma;

class RenderLayer : public Layer {
public:
	virtual void OnAttach() override {
		TextureSpecification spec;
		spec.colorSpace = ColorSpace::RGB;
		m_Texture = CreateRef<Texture>("textures/erling.jpg", spec);

		Renderer2D::SetViewport(Viewport(0, 0, 800, 600));
		m_Camera = Camera(glm::ortho(0.0f, (float)800, 0.0f, (float)600, -1.0f, 100.0f));

		m_Pos = glm::vec2(0.0f);
	}

	virtual void OnUpdate(const DeltaTime&) override {

		static float speed = 1.0f;
		m_Pos.x += speed * ((float)IsKeyPressed(KeyCode::Right) - (float)IsKeyPressed(KeyCode::Left));

		auto m = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos, 0.0f)) * m_Camera.GetProjection();
		static Camera cam(m);

		Renderer2D::Clear();
		Renderer2D::BeginScene(cam);
		Renderer2D::DrawTexturedQuad({ 0, 0 }, m_Texture);
		Renderer2D::EndScene();
	}

	virtual bool OnWindowResize(WindowResizeEvent &e) override {
		Renderer2D::SetViewport(Viewport(0, 0, e.Width, e.Height));
		m_Camera = Camera(glm::ortho(0.0f, (float)e.Width, 0.0f, (float)e.Height, -1.0f, 100.0f));

		return false;
	}

	virtual bool OnKeyPressed(KeyPressedEvent &e) override {
		mlLog("Key pressed: " << (int)e.GetKeyCode());

		if (e.GetKeyCode() == KeyCode::Escape) {
			WindowCloseEvent we;
			Application::Instance->OnEvent((Event&)we);
		}
		return false;
	}

private:
	Ref<Texture> m_Texture;
	Camera m_Camera;
	glm::vec2 m_Pos;
};


class SandboxApp : public Application {
public:
	SandboxApp() : Application() {
		PushLayerTop(Ref<Layer>(new RenderLayer));
	}
};

Application *CreateApplication() {
	return new SandboxApp;
}