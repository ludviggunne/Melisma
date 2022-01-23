#pragma once

#include "melisma/application.h"
#include "melisma/rendering/renderer2D.h"
#include "melisma/pointers.h"

extern melisma::Application *CreateApplication();

// ENTRY POINT --------------------------------------------------------------------------
int main() {

	auto application = CreateApplication();
	application->Run();
	delete application;

#if ML_DEBUG && 0
	std::cout << "Application finished, press enter to exit.";
	std::cin.get();
#endif
}
//---------------------------------------------------------------------------------------