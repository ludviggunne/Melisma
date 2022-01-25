#include "melisma/input/input.h"

#include "melisma/application.h"

namespace melisma {

	// Melisma Todo: Global functions should be function pointers, initialized after application is created
	// (in main). Initially they point to functions that always return false. Maybe bad idea, INDIRECTION.

	bool IsKeyPressed(KeyCode keyCode) 
	{
		return Application::Instance->GetWindow()->IsKeyPressed(keyCode);
	}

	bool IsMouseButtonPressed(MouseCode mouseCode)
	{
		return Application::Instance->GetWindow()->IsMouseButtonPressed(mouseCode);
	}

	glm::vec2 GetMousePos()
	{
		return Application::Instance->GetWindow()->GetMousePos();
	}

}