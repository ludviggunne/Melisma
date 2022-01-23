#include "melisma.h"

using namespace melisma;

#include <format>

class RenderLayer : public Layer {
public:

	virtual void OnUpdate(const DeltaTime&) override {
		Renderer2D::Clear();
		Renderer2D::BeginScene();
		Renderer2D::DrawQuad({ -.5, -.5 }, { 1, 1 }, { 1, 0, 0, 1 });
		Renderer2D::EndScene();
	}

private:
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