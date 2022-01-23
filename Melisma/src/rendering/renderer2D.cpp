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
		// Default settings
		SetBatchSize(1000);
		SetViewport(Viewport(0, 0, 800, 600));


		GLcall(glEnable(GL_BLEND));
		GLcall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Melisma Todo: Implement blending API

		// Create default white texture
		unsigned int white_color = 0xffffffff;
		m_white_texture = Ref<Texture>::Create(&white_color, 1, 1, TextureSpecification{});
		m_white_texture->BindToUnit(0);

		m_texture_count = 0;
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

	void Renderer2D::DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
	{

		if (m_Batch.quad_count >= m_Batch.quad_size)
		{
			EndScene();
			ClearBatch();
		}

		/* Vertices */
		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos, 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(0.0f, 1.0f);
		m_Batch.vertex_buffer_ptr->TexID	= 0.0f;
		m_Batch.vertex_buffer_ptr->Color	= color;
		m_Batch.vertex_buffer_ptr++;

		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(size.x, 0), 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(1.0f, 1.0f);
		m_Batch.vertex_buffer_ptr->TexID	= 0.0f;
		m_Batch.vertex_buffer_ptr->Color	= color;
		m_Batch.vertex_buffer_ptr++;

		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(0, size.y), 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(0.0f, 0.0f);
		m_Batch.vertex_buffer_ptr->TexID	= 0.0f;
		m_Batch.vertex_buffer_ptr->Color	= color;
		m_Batch.vertex_buffer_ptr++;

		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos + size, 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(1.0f, 0.0f);
		m_Batch.vertex_buffer_ptr->TexID	= 0.0f;
		m_Batch.vertex_buffer_ptr->Color	= color;
		m_Batch.vertex_buffer_ptr++;

		/* Indices */
		// Melisma Todo: Construct entire index buffer in Renderer2D::SetBatchSize
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count);
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 1;
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 2;

		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 1;
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 2;
		*(m_Batch.index_buffer_ptr++) = 4 * (m_Batch.quad_count) + 3;

		m_Batch.quad_count++;
	}

	void Renderer2D::DrawTexturedQuad(glm::vec2 pos, const Ref<Texture> &texture, float scale, int u, int v)
	{
		if (m_Batch.quad_count >= m_Batch.quad_size)
		{
			EndScene();
			ClearBatch();
		}

		// Find already bound texture
		float texture_index = 0.0f;
		for (int i = 0; i < m_texture_count; i++)
		{
			if (m_textures[i] == texture)
			{
				// Add one since m_textures[0] is in unit 1 (white texture in unit 0)
				texture_index = (float)(i + 1);
				break;
			}
		}

		if (texture_index == 0.0f)
		{
			if (m_texture_count == ML_MAX_TEXTURES - 2) {
				EndScene();
				ClearBatch();
			}

			m_textures[m_texture_count] = texture;
			texture->BindToUnit(m_texture_count + 1);
			texture_index = (float)(m_texture_count + 1);

			m_texture_count++;
		}


		float w = scale * texture->Width();
		float h = scale * texture->Height();

		float u_unit = 1.0f / texture->HTiles();
		float v_unit = 1.0f / texture->VTiles();

		float ut = u_unit * u;
		float vt = v_unit * v;

		/* Vertices */
		// Melisma Todo: construct vecs by member?
		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos, 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(ut, vt + v_unit);
		m_Batch.vertex_buffer_ptr->TexID = texture_index;
		m_Batch.vertex_buffer_ptr->Color = { 1, 1, 1, 1 };
		m_Batch.vertex_buffer_ptr++;

		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(w, 0), 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(ut + u_unit, vt + v_unit);
		m_Batch.vertex_buffer_ptr->TexID = texture_index;
		m_Batch.vertex_buffer_ptr->Color = { 1, 1, 1, 1 };
		m_Batch.vertex_buffer_ptr++;

		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(0, h), 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(ut, vt);
		m_Batch.vertex_buffer_ptr->TexID = texture_index;
		m_Batch.vertex_buffer_ptr->Color = { 1, 1, 1, 1 };
		m_Batch.vertex_buffer_ptr++;

		m_Batch.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(w, h), 1.0f);
		m_Batch.vertex_buffer_ptr->TexCoord = glm::vec2(ut + u_unit, vt);
		m_Batch.vertex_buffer_ptr->TexID = texture_index;
		m_Batch.vertex_buffer_ptr->Color = { 1, 1, 1, 1 };
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

		ClearBatch();
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

	void Renderer2D::ClearBatch()
	{
		/* Reset buffer pointers, textures and quad count */
		m_Batch.vertex_buffer_ptr	= m_Batch.vertex_buffer;
		m_Batch.index_buffer_ptr	= m_Batch.index_buffer;

		m_texture_count				= 0;

		m_Batch.quad_count			= 0;
	}
}
