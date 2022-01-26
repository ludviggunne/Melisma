#include "melisma.h"

using namespace melisma;

class ExampleLayer : public Layer {
	virtual void OnAttach() override {

	}

	virtual void OnUpdate(const DeltaTime &dt) override {

	}
};

class SandboxApp : public Application {
public:
	using Application::Application;

	virtual void Init() override {

	}
};

Application *CreateApplication() {
	return new SandboxApp;
}