#include "melisma/rendering/renderer2D.h"

#include <sstream>
#include <fstream>

#include "glad/glad.h"
#include "stb_image.h"
#include "glm/ext.hpp"

#include "glcall.h"
#include "..\..\include\melisma\rendering\renderer2D.h"

// Melisma Todo: Remake renderer to contain shaders, textures and uniforms

namespace melisma {

	Renderer2D::Renderer2D()
	{ 
		m_VAO = Ref<VertexArrayObject>::Create(DefaultVertexBufferLayout<Vertex>());
		SetBatchSize(1000);
		SetViewport(Viewport(0, 0, 800, 600));


		GLcall(glEnable(GL_BLEND));
		GLcall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Melisma Todo: Implement blending API
	}

	void Renderer2D::SetBatchSize(uint32_t size)
	{
		if (size == m_Batch.quad_size) return;

		if (m_Batch.vertex_buffer) delete[] m_Batch.vertex_buffer;
		if (m_Batch.vertex_buffer) delete[] m_Batch.vertex_buffer;


		m_Batch.vertex_buffer		= new Vertex  [(size_t)size * 4];
		m_Batch.index_buffer		= new uint32_t[(size_t)size * 6];

		m_Batch.vertex_buffer_ptr	= m_Batch.vertex_buffer;
		m_Batch.index_buffer_ptr	= m_Batch.index_buffer;

		m_Batch.quad_count			= 0;
		m_Batch.quad_size			= size;
	}

	void Renderer2D::DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color, float texture_slot)
	{

		if (m_Batch.quad_count >= m_Batch.quad_size)
		{
			EndScene();
			Flush();
		}

		/* Vertices */
		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos, 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(0.0f, 1.0f);
		m_Batch.vertex_buffer_ptr->TexID	= texture_slot;
		m_Batch.vertex_buffer_ptr->Color	= color;
		m_Batch.vertex_buffer_ptr++;

		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(size.x, 0), 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(1.0f, 1.0f);
		m_Batch.vertex_buffer_ptr->TexID	= texture_slot;
		m_Batch.vertex_buffer_ptr->Color	= color;
		m_Batch.vertex_buffer_ptr++;

		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(0, size.y), 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(0.0f, 0.0f);
		m_Batch.vertex_buffer_ptr->TexID	= texture_slot;
		m_Batch.vertex_buffer_ptr->Color	= color;
		m_Batch.vertex_buffer_ptr++;

		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos + size, 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(1.0f, 0.0f);
		m_Batch.vertex_buffer_ptr->TexID	= texture_slot;
		m_Batch.vertex_buffer_ptr->Color	= color;
		m_Batch.vertex_buffer_ptr++;

		/* Indices */
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count);
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 1;
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 2;

		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 1;
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 2;
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 3;

		m_Batch.quad_count++;
	}

	void Renderer2D::Clear(glm::vec4 color) const
	{
		GLcall(glClearColor(color.r, color.g, color.b, color.a));
		GLcall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Renderer2D::SetViewport(Viewport viewport)
	{
		GLcall(glViewport(
			viewport.X,  
			viewport.Y,
			viewport.Width, 
			viewport.Height
		));

		m_Viewport = viewport;
	}

	

	void Renderer2D::BeginScene(const Camera &camera)
	{
		m_Info.draw_calls = 0;

		Flush();
	}

	void Renderer2D::EndScene()
	{
		/* Bind and populate buffers */
		m_VAO->Bind();
		m_VAO->VertexData(m_Batch.vertex_buffer, 4 * (size_t)m_Batch.quad_count * sizeof(Vertex));
		m_VAO->IndexData(m_Batch.index_buffer,   6 * (size_t)m_Batch.quad_count * sizeof(uint32_t));


		/* Draw elements */
		m_VAO->Draw(Primitive::Triangles, (size_t)m_Batch.quad_count * 6);


		/* Finish */
		m_VAO->Unbind();

		m_Info.draw_calls++;
	}

	void Renderer2D::Flush()
	{
		/* Reset buffer pointers and quad count */
		m_Batch.vertex_buffer_ptr	= m_Batch.vertex_buffer;
		m_Batch.index_buffer_ptr	= m_Batch.index_buffer;

		m_Batch.quad_count			= 0;
	}
}
