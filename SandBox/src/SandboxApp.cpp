#include "melisma.h"

using namespace melisma;

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

		std::vector<Ref<Texture>> textures;

		/* Textures */
		TextureSpecification tspec;

		unsigned int white = 0xffffffff;
		textures.push_back(Ref<Texture>(&white, 1, 1, tspec));

		tspec.colorSpace = ColorSpace::RGBA;
		tspec.magFilter = Filter::NEAREST;
		textures.push_back(Ref<Texture>("textures/forest/Layer_0000_9.png",		 tspec));
		textures.push_back(Ref<Texture>("textures/forest/Layer_0001_8.png",		 tspec));
		textures.push_back(Ref<Texture>("textures/forest/Layer_0002_7.png",		 tspec));
		textures.push_back(Ref<Texture>("textures/forest/Layer_0003_6.png",		 tspec));
		textures.push_back(Ref<Texture>("textures/forest/Layer_0004_Lights.png", tspec));
		textures.push_back(Ref<Texture>("textures/forest/Layer_0006_4.png",		 tspec));
		textures.push_back(Ref<Texture>("textures/forest/Layer_0007_Lights.png", tspec));
		textures.push_back(Ref<Texture>("textures/forest/Layer_0009_2.png",		 tspec));
		textures.push_back(Ref<Texture>("textures/forest/Layer_0010_1.png",		 tspec));
		textures.push_back(Ref<Texture>("textures/forest/Layer_0011_0.png",		 tspec));

		for (int i = 0; i < textures.size(); i++) {
			textures[i]->BindToSlot(i);
		}

		int textureSlots[32];
		for (int i = 0; i < 32; i++) textureSlots[i] = i;

		/* Shaders */
		ShaderProgram program;
		program.Create("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
		program.Use();

		program.SetUniformArray(program.GetUniformLocation("u_Textures"), 32, textureSlots);
		int viewLoc = program.GetUniformLocation("u_View");

		int width =  textures[1]->Width();
		int height = textures[1]->Height();

		glm::mat4 viewBase = glm::mat4(1.0f);//glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.01f, 100.0f);
		viewBase = glm::translate(viewBase, glm::vec3(-1.0f, -1.0f, 0.0f));
		viewBase = glm::scale(viewBase, glm::vec3(2.0f / width, 2.0f / height, 1.0f));

		m_Window->SetSize(2 * width, 2 * height);
		//m_Window->GetFrameBufferSize(width, height);
		renderer.SetViewport({ 0, 0, 2 * width, 2 * height });

		width *= 1.5f;
		height *= 1.5f;

		while (m_Running) { 
			renderer.Clear(glm::vec4(glm::vec3(0.2f), 0.2f));

			program.SetUniform(viewLoc, viewBase);

			renderer.BeginScene();

			for (int i = textures.size() - 1; i > 0; i--) {
				int offset = (int)((textures.size() - i) * tOffset / textures.size());
				offset %= width;

				renderer.DrawQuad(
					{-width + offset, 0},
					{ width, height },
					{1.0f, 1.0f, 1.0f, 1.0f},
					i);
				renderer.DrawQuad(
					{ offset, 0 },
					{ width, height },
					{ 1.0f, 1.0f, 1.0f, 1.0f },
					i);
				renderer.DrawQuad(
					{ width + offset, 0 },
					{ width, height },
					{ 1.0f, 1.0f, 1.0f, 1.0f },
					i);
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