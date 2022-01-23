#include "melisma/window.h"
#include "melisma/core.h"

#include "melisma/event/window_event.h"
#include "melisma/event/key_event.h"
#include "melisma/event/mouse_event.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "..\include\melisma\window.h"

#define mlGetUserData(name, window) auto name = (UserData*)glfwGetWindowUserPointer((GLFWwindow *)window)

namespace melisma {

	Window::Window(int width, int height, const char *title)
	{
		m_UserData.Width = width;
		m_UserData.Height = height;

		/* Init GLFW */
		mlVerifyMsg(glfwInit(), "Couldn't initialize GLFW");


		/* Create window */
		mlVerifyMsg(m_NativeHandle = glfwCreateWindow(width, height, title, NULL, NULL), "Couldn't create GLFW window");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwMakeContextCurrent((GLFWwindow*)m_NativeHandle);
		glfwSwapInterval(1);

		/* Set user data pointer */
		glfwSetWindowUserPointer((GLFWwindow*)m_NativeHandle, &m_UserData);
		

		/* Init glad */
		mlVerifyMsg(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Couldn't initialize GLAD");

		/* Set callback functions */
		/* WindowCloseEvent */
		glfwSetWindowCloseCallback((GLFWwindow *)m_NativeHandle, [](GLFWwindow *window) {
			mlGetUserData(data, window);

			WindowCloseEvent e;
			data->EventCallback(e);
		});

		/* WindowResizeEvent */
		glfwSetWindowSizeCallback((GLFWwindow *)m_NativeHandle, [](GLFWwindow *window, int w, int h) {
			mlGetUserData(data, window);

			data->Width = w;
			data->Height = h;

			WindowResizeEvent e(w, h);
			data->EventCallback(e);
		});

		/* WindowMovedEvent */
		glfwSetWindowPosCallback((GLFWwindow *)m_NativeHandle, [](GLFWwindow *window, int xpos, int ypos) {
			mlGetUserData(data, window);

			WindowMovedEvent e(xpos, ypos);
			data->EventCallback(e);
		});

		/* KeyEvent */
		glfwSetKeyCallback((GLFWwindow *)m_NativeHandle, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
			mlGetUserData(data, window);

			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent e((KeyCode)key, false);
					data->EventCallback(e);
					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent e((KeyCode)key, true);
					data->EventCallback(e);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent e((KeyCode)key);
					data->EventCallback(e);
					break;
				}
			}
		});

		
		/* MouseButtonEvent */
		glfwSetMouseButtonCallback((GLFWwindow *)m_NativeHandle, [](GLFWwindow *window, int button, int action, int mods) {
			mlGetUserData(data, window);

			switch (action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent e((MouseCode)button);
				data->EventCallback(e);
				break;
			}

			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent e((MouseCode)button);
				data->EventCallback(e);
				break;
			}
			}
		});
	}

	Window::~Window()
	{
		mlLog("Window destructed");
		glfwTerminate();
	}
	void Window::OnUpdate(const DeltaTime &) const
	{
		glfwPollEvents();
		glfwSwapBuffers((GLFWwindow*)m_NativeHandle);
	}

	void Window::SetResizable(bool resizable) const
	{
		glfwSetWindowAttrib((GLFWwindow*)m_NativeHandle, GLFW_RESIZABLE, resizable);
	}

	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize((GLFWwindow *)m_NativeHandle, width, height);
		m_UserData.Width = width;
		m_UserData.Height = height;
	}

	void Window::GetFrameBufferSize(int &width, int &height) const
	{
		glfwGetFramebufferSize((GLFWwindow *)m_NativeHandle, &width, &height);
	}

	bool Window::IsKeyPressed(KeyCode keyCode) const
	{
		return glfwGetKey((GLFWwindow *)m_NativeHandle, (int)keyCode);
	}
}