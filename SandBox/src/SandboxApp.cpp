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