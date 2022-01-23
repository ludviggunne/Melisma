#include "melisma.h"

using namespace melisma;

#include <format>

class SandboxApp : public Application {
public:
	SandboxApp() : Application() {}
	virtual ~SandboxApp() override {}

	Renderer2D renderer;

	virtual void Run() override {

		while (m_Running) {

			renderer.Clear();
			renderer.BeginScene();

			renderer.EndScene();

			m_LayerStack.OnUpdate(DeltaTime()); 
			m_Window->OnUpdate(DeltaTime());
		}
	}
};

Application *CreateApplication() {
	return new SandboxApp;
}