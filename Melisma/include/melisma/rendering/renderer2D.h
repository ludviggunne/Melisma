#pragma once
#include "melisma/core.h"

#include "vertex.h"
#include "vertex_array_object.h"
#include "shader_program.h"
#include "texture.h"
#include "camera.h"


/* Implementation of 2D batch renderer */
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

		void DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color, float texture_slot);
		void Clear(glm::vec4 color = {0, 0, 0, 1}) const;

		void SetViewport(Viewport);

		void BeginScene(const Camera &camera = Camera());
		void EndScene();

		unsigned int GetDrawCalls() const { return m_Info.draw_calls; }

	public:

	private:
		void Flush();


	private:
		Ref<VertexArrayObject> m_VAO;
		Viewport m_Viewport;


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