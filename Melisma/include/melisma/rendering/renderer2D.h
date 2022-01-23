#pragma once
#include "melisma/core.h"
#include "melisma/pointers.h"

#include "vertex.h"
#include "vertex_array_object.h"
#include "shader_program.h"
#include "texture.h"
#include "camera.h"


/* Implementation of 2D batch renderer */
// Melisma Todo: Singleton
namespace melisma {

	struct Viewport {
		int X = 0;
		int Y = 0;
		int Width = 100;
		int Height = 100;
	};

	class melismaAPI Renderer2D {
	public:

		/* Setup */
		Renderer2D();

		void SetBatchSize(uint32_t);

		void DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color);
		void DrawTexturedQuad(glm::vec2 pos, const Ref<Texture> &texture, float scale = 1.0f, int u = 0, int v = 0);

		void Clear(glm::vec4 color = {0, 0, 0, 1}) const;

		void SetViewport(Viewport);

		void BeginScene(const Camera &camera = Camera());
		void EndScene();

	public:
		static void Init();	   // Melisma Todo: impl
		static void ShutDown();// Melisma Todo: impl

	private:
		void ClearBatch();


	private:
		Ref<VertexArrayObject> m_VAO;
		Viewport m_Viewport;

		// First texture is white texture
		Ref<Texture> m_textures[ML_MAX_TEXTURES - 1];
		Ref<Texture> m_white_texture;
		unsigned int m_texture_count;


		struct Batch {
			Vertex *vertex_buffer		= nullptr;
			uint32_t *index_buffer		= nullptr;

			Vertex *vertex_buffer_ptr	= nullptr;
			uint32_t *index_buffer_ptr	= nullptr;

			uint32_t quad_count			= 0;
			uint32_t quad_size			= 0;

		} m_Batch;

		struct Info {
			unsigned int draw_calls = 0;
		} m_Info;
	};
}