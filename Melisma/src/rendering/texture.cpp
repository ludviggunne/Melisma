#include "melisma/rendering/texture.h"

#include "stb_image.h"
#include "glad/glad.h"

#include "glcall.h"
#include "..\..\include\melisma\rendering\texture.h"

namespace melisma {

	Texture::Texture(const char *filename, TextureSpecification spec)
	{
		int prefered_channels = 0;
		switch (spec.colorSpace) {
		case ColorSpace::RGB:
			prefered_channels = 3;
			break;

		case ColorSpace::RGBA:
			prefered_channels = 4;
		}

		int width, height, n_channels;
		unsigned char *image_data = stbi_load(filename, &width, &height, &n_channels, prefered_channels);
		unsigned char error_tex[] = { 0xff, 0x00, 0xff };

		//GLcall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
		bool load_success = true;
		if (!image_data) {
			mlLog("Failed to load texture image from path " << filename);
			stbi_image_free(image_data);

			/* Revert to magenta error texture and default specification */
			width  = 1;
			height = 1;

			image_data = error_tex;
			spec       = TextureSpecification{};

			load_success = false;
		}

		m_Width  = width;
		m_Height = height;
		m_hTiles = spec.hTiles;
		m_vTiles = spec.vTiles;

		GLcall(glGenTextures(1, &m_RendererID));

		GLcall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,		(GLenum)spec.sWrap));
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,		(GLenum)spec.tWrap));
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,	(GLenum)spec.magFilter));
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,	(GLenum)spec.magFilter));


		GLcall(glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)spec.colorSpace,
			width, height, 0, (GLenum)spec.colorSpace, GL_UNSIGNED_BYTE, image_data));

		GLcall(glBindTexture(GL_TEXTURE_2D, 0));

		if(load_success) stbi_image_free(image_data);

		mlDefineDebugName("Texture: " << filename);
	}

	Texture::Texture(const void *data, int width, int height, TextureSpecification spec)
	{
		m_Width = width;
		m_Height = height;
		m_hTiles = spec.hTiles;
		m_vTiles = spec.vTiles;


		GLcall(glGenTextures(1, &m_RendererID));

		GLcall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)spec.sWrap));
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)spec.tWrap));
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)spec.magFilter));
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)spec.magFilter));


		GLcall(glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)spec.colorSpace,
			width, height, 0, (GLenum)spec.colorSpace, GL_UNSIGNED_BYTE, data));

		GLcall(glBindTexture(GL_TEXTURE_2D, 0));

		mlDefineDebugName("Texture: no source");
	}

	Texture::~Texture()
	{
		GLcall(glDeleteTextures(1, &m_RendererID));
	}

	void Texture::BindToSlot(unsigned int slot)
	{
		GLcall(glActiveTexture(GL_TEXTURE0 + slot));
		GLcall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void Texture::BindContiguous(Texture *textures, unsigned int count)
	{
		for (unsigned int i = 0; i < count; i++)
			textures[i].BindToSlot(i);
	}

}