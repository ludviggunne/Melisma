#include "melisma.h"

using namespace melisma;

#include <format>

class RenderLayer : public Layer {
public:
	virtual void OnAttach() override {
		TextureSpecification spec;
		spec.colorSpace = ColorSpace::RGB;
		m_Texture = Ref<Texture>::Create("textures/erling.jpg", spec);
	}

	virtual void OnUpdate(const DeltaTime&) override {
		Renderer2D::Clear();
		Renderer2D::BeginScene(m_Camera);
		Renderer2D::DrawTexturedQuad({ 0, 0 }, m_Texture);
		Renderer2D::EndScene();
	}

	virtual bool OnWindowResize(WindowResizeEvent &e) override {
		Renderer2D::SetViewport(Viewport(0, 0, e.Width, e.Height));
		m_Camera = Camera(glm::ortho(0.0f, (float)e.Width, 0.0f, (float)e.Height, -1.0f, 100.0f));

		return false;
	}

private:
	Ref<Texture> m_Texture;
	Camera m_Camera;
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