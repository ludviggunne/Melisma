#include "melisma/input/input.h"

#include "melisma/application.h"

namespace melisma {

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