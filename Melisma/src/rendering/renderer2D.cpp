#include "melisma/rendering/renderer2D.h"

#include <sstream>
#include <fstream>

#include "glad/glad.h"
#include "stb_image.h"
#include "glm/ext.hpp"

#include "glcall.h"
#include "..\..\include\melisma\rendering\renderer2D.h"

namespace melisma {

	struct RenderData {
		Scope<VertexArrayObject> vertex_array;
		Viewport viewport;

		// Textures
		Ref<Texture> texture_buffer[ML_MAX_TEXTURES - 1];
		Ref<Texture> white_texture;
		unsigned int texture_count = 0;


		// Shader
		Scope<ShaderProgram> program; // Melisma Todo: Change to melisma::Scope
		int view_location = -1;


		// Batch
		Vertex *vertex_buffer = nullptr;
		uint32_t *index_buffer = nullptr;

		Vertex *vertex_buffer_ptr = nullptr;
		uint32_t *index_buffer_ptr = nullptr;

		uint32_t quad_count = 0;
		uint32_t quad_size = 0;


		// Info
		unsigned int draw_calls = 0;
	};

	static RenderData s_Data;

	void Renderer2D::Init()
	{
		// Default settings
		SetBatchSize(1000);
		SetViewport(Viewport(0, 0, 800, 600));


		GLcall(glEnable(GL_BLEND));
		GLcall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Melisma Todo: Implement blending API


		// Vertex array
		s_Data.vertex_array = CreateScope<VertexArrayObject>(DefaultVertexBufferLayout<Vertex>());


		// Shaders
		s_Data.program = CreateScope<ShaderProgram>();
		s_Data.program->Create("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
		s_Data.view_location = s_Data.program->GetUniformLocation("u_View");


		// Init texture units
		{
			int texture_location = s_Data.program->GetUniformLocation("u_Textures");
			int texture_units[ML_MAX_TEXTURES];
			for (int i = 0; i < ML_MAX_TEXTURES; i++)
				texture_units[i] = i;
			s_Data.program->SetUniformArray(texture_location, ML_MAX_TEXTURES, texture_units);
		}
		

		// Create default white texture
		unsigned int white_color = 0xffffffff;
		s_Data.white_texture = CreateRef<Texture>(&white_color, 1, 1, TextureSpecification{});
	}

	void Renderer2D::ShutDown()
	{
		// Clear resources (must be reset since static variables scopes exceed lifetime of context (melisma::Window)
		s_Data.vertex_array.reset();
		s_Data.program.reset();

		for (int i = 0; i < ML_MAX_TEXTURES - 1; i++) {
			s_Data.texture_buffer[i].reset();
		}

		s_Data.white_texture.reset();
	}

	void Renderer2D::SetBatchSize(uint32_t size)
	{
		if (size == s_Data.quad_size) return;

		if (s_Data.vertex_buffer) delete[] s_Data.vertex_buffer;
		if (s_Data.vertex_buffer) delete[] s_Data.vertex_buffer;


		s_Data.vertex_buffer		= new Vertex  [(size_t)size * 4];
		s_Data.index_buffer			= new uint32_t[(size_t)size * 6];

		s_Data.vertex_buffer_ptr	= s_Data.vertex_buffer;
		s_Data.index_buffer_ptr 	= s_Data.index_buffer;

		s_Data.quad_count			= 0;
		s_Data.quad_size			= size;
	}

	void Renderer2D::DrawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color)
	{

		if (s_Data.quad_count >= s_Data.quad_size)
		{
			EndScene();
			ClearBatch();
		}

		/* Vertices */
		s_Data.vertex_buffer_ptr->Position = glm::vec3(pos, 1.0f);
		s_Data.vertex_buffer_ptr->TexCoord = glm::vec2(0.0f, 1.0f);
		s_Data.vertex_buffer_ptr->TexID	= 0.0f;
		s_Data.vertex_buffer_ptr->Color	= color;
		s_Data.vertex_buffer_ptr++;

		s_Data.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(size.x, 0), 1.0f);
		s_Data.vertex_buffer_ptr->TexCoord = glm::vec2(1.0f, 1.0f);
		s_Data.vertex_buffer_ptr->TexID	= 0.0f;
		s_Data.vertex_buffer_ptr->Color	= color;
		s_Data.vertex_buffer_ptr++;

		s_Data.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(0, size.y), 1.0f);
		s_Data.vertex_buffer_ptr->TexCoord = glm::vec2(0.0f, 0.0f);
		s_Data.vertex_buffer_ptr->TexID	= 0.0f;
		s_Data.vertex_buffer_ptr->Color	= color;
		s_Data.vertex_buffer_ptr++;

		s_Data.vertex_buffer_ptr->Position = glm::vec3(pos + size, 1.0f);
		s_Data.vertex_buffer_ptr->TexCoord = glm::vec2(1.0f, 0.0f);
		s_Data.vertex_buffer_ptr->TexID	= 0.0f;
		s_Data.vertex_buffer_ptr->Color	= color;
		s_Data.vertex_buffer_ptr++;

		/* Indices */
		// Melisma Todo: Construct entire index buffer in Renderer2D::SetBatchSize
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count);
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 1;
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 2;

		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 1;
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 2;
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 3;

		s_Data.quad_count++;
	}

	void Renderer2D::DrawTexturedQuad(glm::vec2 pos, const Ref<Texture> &texture, float scale, int u, int v)
	{
		DrawTexturedQuad(pos, texture, scale * glm::vec2(texture->Width(), texture->Height()), u, v); // Melisma Todo: Forwarding arguments (const&?)
	}

	void Renderer2D::DrawTexturedQuad(glm::vec2 pos, const Ref<Texture> &texture, glm::vec2 size, int u, int v)
	{
		if (s_Data.quad_count >= s_Data.quad_size)
		{
			EndScene();
			ClearBatch();
		}

		// Find already bound texture
		float texture_index = 0.0f;
		for (int i = 0; i < s_Data.texture_count; i++)
		{
			if (s_Data.texture_buffer[i] == texture)
			{
				// Add one since s_Data.texture_buffer[0] is in unit 1 (white texture in unit 0)
				texture_index = (float)(i + 1);
				break;
			}
		}

		if (texture_index == 0.0f)
		{
			if (s_Data.texture_count == ML_MAX_TEXTURES - 2) {
				EndScene();
				ClearBatch();
				s_Data.texture_count = 0;
			}

			s_Data.texture_buffer[s_Data.texture_count] = texture;
			texture->BindToUnit(s_Data.texture_count + 1);
			texture_index = (float)(s_Data.texture_count + 1);

			s_Data.texture_count++;
		}

		float u_unit = 1.0f / texture->HTiles();
		float v_unit = 1.0f / texture->VTiles();

		float ut = u_unit * u;
		float vt = v_unit * v;

		/* Vertices */
		// Melisma Todo: construct vecs by member?
		s_Data.vertex_buffer_ptr->Position = glm::vec3(pos, 1.0f);
		s_Data.vertex_buffer_ptr->TexCoord = glm::vec2(ut, vt + v_unit);
		s_Data.vertex_buffer_ptr->TexID = texture_index;
		s_Data.vertex_buffer_ptr->Color = glm::vec4(1, 1, 1, 1);
		s_Data.vertex_buffer_ptr++;

		s_Data.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(size.x, 0), 1.0f);
		s_Data.vertex_buffer_ptr->TexCoord = glm::vec2(ut + u_unit, vt + v_unit);
		s_Data.vertex_buffer_ptr->TexID = texture_index;
		s_Data.vertex_buffer_ptr->Color = glm::vec4(1, 1, 1, 1);
		s_Data.vertex_buffer_ptr++;

		s_Data.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(0, size.y), 1.0f);
		s_Data.vertex_buffer_ptr->TexCoord = glm::vec2(ut, vt);
		s_Data.vertex_buffer_ptr->TexID = texture_index;
		s_Data.vertex_buffer_ptr->Color = glm::vec4(1, 1, 1, 1);
		s_Data.vertex_buffer_ptr++;

		s_Data.vertex_buffer_ptr->Position = glm::vec3(pos + glm::vec2(size.x, size.y), 1.0f);
		s_Data.vertex_buffer_ptr->TexCoord = glm::vec2(ut + u_unit, vt);
		s_Data.vertex_buffer_ptr->TexID = texture_index;
		s_Data.vertex_buffer_ptr->Color = glm::vec4(1, 1, 1, 1);
		s_Data.vertex_buffer_ptr++;

		/* Indices */
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count);
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 1;
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 2;

		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 1;
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 2;
		*(s_Data.index_buffer_ptr++) = 4 * (s_Data.quad_count) + 3;

		s_Data.quad_count++;
	}

	void Renderer2D::Clear(glm::vec4 color)
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

		s_Data.viewport = viewport;
	}

	

	void Renderer2D::BeginScene(const Camera &camera)
	{
		s_Data.draw_calls = 0;
		s_Data.program->SetUniform(s_Data.view_location, camera.GetProjection());
		s_Data.white_texture->BindToUnit(0);
		ClearBatch();
	}

	void Renderer2D::EndScene()
	{
		/* Bind and populate buffers */
		s_Data.vertex_array->Bind();
		s_Data.vertex_array->VertexData(s_Data.vertex_buffer, 4 * (size_t)s_Data.quad_count * sizeof(Vertex));
		s_Data.vertex_array->IndexData(s_Data.index_buffer,   6 * (size_t)s_Data.quad_count * sizeof(uint32_t));


		/* Draw elements */
		s_Data.vertex_array->Draw(Primitive::Triangles, (size_t)s_Data.quad_count * 6);


		/* Finish */
		s_Data.vertex_array->Unbind();

		s_Data.draw_calls++;
	}


	void Renderer2D::ClearBatch()
	{
		/* Reset buffer pointers, textures and quad count */
		s_Data.vertex_buffer_ptr	= s_Data.vertex_buffer;
		s_Data.index_buffer_ptr		= s_Data.index_buffer;

		s_Data.quad_count			= 0;
	}
}
