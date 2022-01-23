#include "melisma.h"

using namespace melisma;

#include <format>

class SandboxApp : public Application {
public:
	SandboxApp() : Application(), tOffset(0), tVelocity(0), tDir(1) {}
	virtual ~SandboxApp() override {}

	Renderer2D renderer;

	float tOffset;
	float tVelocity;
	int tDir;

	virtual void Run() override {

		m_Window->SetResizable(false);


		/* Textures */
		std::vector<Ref<Texture>> textures;
		textures.reserve(12);

		TextureSpecification tex_spec;
		tex_spec.colorSpace = ColorSpace::RGBA;
		tex_spec.magFilter  = Filter::Nearest;

		for (int i = 0; i < 12; i++) {
			auto path = std::format("textures/forest/Layer{:02d}.png", i);

			textures.push_back(Ref<Texture>::Create(path.c_str(), tex_spec));
			mlLog(textures[i]->_debugName);
		}

		int textureSlots[32]; // Melisma Todo: move to renderer
		for (int i = 0; i < 32; i++) 
			textureSlots[i] = i;


		/* Shaders */
		ShaderProgram program;
		program.Create("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
		program.Use();

		program.SetUniformArray(program.GetUniformLocation("u_Textures"), 32, textureSlots);
		int viewLoc = program.GetUniformLocation("u_View");


		int width =  textures[0]->Width();
		int height = textures[0]->Height();

		glm::mat4 viewBase = glm::mat4(1.0f);//*/glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.01f, 100.0f); // Melisma Todo: Figure out 
		viewBase = glm::translate(viewBase, glm::vec3(-1.0f, -1.0f, 0.0f));
		viewBase = glm::scale(viewBase, glm::vec3(2.0f / width, 2.0f / height, 1.0f));

		m_Window->SetSize(width, height);
		//m_Window->GetFrameBufferSize(width, height);
		renderer.SetViewport({ 0, 0, width, height });

		while (m_Running) {
			renderer.Clear(glm::vec4(glm::vec3(0.2f), 0.2f));

			program.SetUniform(viewLoc, viewBase);

			renderer.BeginScene();

			for (int i = (int)textures.size() - 1; i >= 0; i--) {
				int offset = (int)((textures.size() - i) * tOffset / textures.size());
				offset %= width;

				renderer.DrawTexturedQuad({ -width + offset, 0 }, textures[i]);
				renderer.DrawTexturedQuad({ offset, 0 }, textures[i]);
				renderer.DrawTexturedQuad({ width + offset, 0 }, textures[i]);
			}

			renderer.EndScene();

			float panSpeed = 6.0f;
			float damping = .05f;
			if (IsKeyPressed(KeyCode::Right)) {
				tVelocity = panSpeed;
				tDir = -1;
			}
			if (IsKeyPressed(KeyCode::Left)) {
				tVelocity = panSpeed;
				tDir = 1;
			}

			tOffset += tVelocity * tDir;
			tVelocity -= damping;
			tVelocity = tVelocity <= 0 ? 0 : tVelocity;

			m_LayerStack.OnUpdate(DeltaTime()); 
			m_Window->OnUpdate(DeltaTime());
		}
	}

	virtual bool OnWindowResize(WindowResizeEvent &e) override {
		mlLog("WindowResizeEvent: " << e.Width << ", " << e.Height);
		return false;
	}

	virtual bool OnKeyPressed(KeyPressedEvent &e) override {
		if (e.GetKeyCode() == KeyCode::Escape)
			m_Running = false;

		if (!e.IsRepeated())
			mlLog("KeyPressedEvent: " << (int)e.GetKeyCode());

		return true;
	}

	virtual bool OnWindowMoved(WindowMovedEvent &e) override {
		mlLog("WindowMovedEvent: " << e.GetXPos() << ", " << e.GetYPos());

		return true;
	}

	virtual bool OnMouseButtonPressed(MouseButtonPressedEvent &e) override {
		mlLog("MouseButtonPressedEvent: " << (int)e.GetMouseCode());

		return true;
	}
};

Application *CreateApplication() {
	return new SandboxApp;
}