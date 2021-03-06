#pragma once
#include "melisma/core.h"
#include "melisma/pointers.h"

#include "vertex.h"
#include "vertex_array_object.h"
#include "shader_program.h"
#include "texture.h"
#include "camera.h"
#include "viewport.h"


/* Implementation of 2D batch renderer */
namespace melisma {

	class melismaAPI Renderer2D {
	public:
		static void Init();	   
		static void ShutDown();

		Renderer2D()                               = delete;
		Renderer2D(const Renderer2D &)             = delete;
		Renderer2D operator = (const Renderer2D &) = delete;

		static void SetBatchSize(uint32_t);

		static void DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color);
		static void DrawTexturedQuad(glm::vec2 pos, const Ref<Texture> &texture, float scale = 1.0f, int u = 0, int v = 0);
		static void DrawTexturedQuad(glm::vec2 pos, const Ref<Texture> &texture, glm::vec2 size, int u = 0, int v = 0);

		static void Clear(glm::vec4 color = glm::vec4(0, 0, 0, 1));

		static void SetViewport(Viewport);

		static void BeginScene(const Camera &camera);
		static void EndScene();


	private:
		static void ClearBatch();
	};
}