#pragma once

#include "melisma/application.h"
#include "melisma/rendering/renderer2D.h"
#include "melisma/pointers.h"

extern melisma::Application *CreateApplication();

// ENTRY POINT --------------------------------------------------------------------------
int main() {

	melisma::Application *application = CreateApplication();

	application->Run();

	delete application;
}
//---------------------------------------------------------------------------------------