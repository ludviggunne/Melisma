#pragma once
#include "melisma/core.h"

namespace melisma {

	enum class Wrap {
		Repeat		    = 0x2901,
		ClampToEdge     = 0x812F,
		MirroredRepeat  = 0x8370
	};

	enum class Filter {
		Nearest = 0x2600,
		Linear  = 0x2601
	};

	enum class ColorSpace {
		RGB = 0x1907,
		RGBA = 0x1908
	};

	struct TextureSpecification {
		ColorSpace colorSpace	= ColorSpace::RGB;

		Filter magFilter		= Filter::Nearest;
		Filter minFilter		= Filter::Nearest;

		Wrap sWrap				= Wrap::Repeat;
		Wrap tWrap				= Wrap::Repeat;

		unsigned int hTiles		= 1;
		unsigned int vTiles		= 1;
	};

	class melismaAPI Texture {
	public:
		Texture()							 = delete;
		Texture(const Texture &)			 = delete;
		Texture operator =(const Texture &)  = delete;
		Texture(Texture &&)					 = delete;
		Texture operator =(Texture &&)		 = delete;

		Texture(const char *filename, TextureSpecification spec);
		Texture(const void *data, int width, int height, TextureSpecification spec);
		~Texture();

		void BindToSlot(int slot);
		int GetSlot() const { return m_Slot; }

		int Width() const { return m_Width; }
		int Height() const { return m_Height; }

		int HTiles() const { return m_hTiles; }
		int VTiles() const { return m_vTiles; }

	public:
		static void BindContiguous(Texture *textures, unsigned int count);

	private:
		unsigned int m_RendererID;
		int m_Slot;

		unsigned int m_Width;
		unsigned int m_Height;

		unsigned int m_hTiles;
		unsigned int m_vTiles;

		mlDeclareDebugName;
	};

}