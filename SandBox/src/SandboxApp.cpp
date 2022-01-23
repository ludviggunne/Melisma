#include "melisma.h"

using namespace melisma;

#include <format>

class SandboxApp : public Application {
public:
	SandboxApp() : Application() {}
	virtual ~SandboxApp() override {}
};

Application *CreateApplication() {
	return new SandboxApp;
}