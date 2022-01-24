#pragma once

#include "melisma/application.h"
#include "melisma/rendering/renderer2D.h"
#include "melisma/pointers.h"
#include "melisma/input/input.h"

extern melisma::Application *CreateApplication();

// ENTRY POINT --------------------------------------------------------------------------
int main() {

	melisma::Application::Instance = CreateApplication();
	melisma::Application::Instance->Run();
	delete melisma::Application::Instance;

#if ML_DEBUG && 0
	std::cout << "Application finished, press enter to exit.";
	std::cin.get();
#endif
}
//---------------------------------------------------------------------------------------