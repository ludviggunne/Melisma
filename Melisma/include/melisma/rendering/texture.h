#pragma once
#include "melisma/core.h"

namespace melisma {

	enum class Wrap {
		REPEAT		    = 0x2901,
		CLAMP_TO_EDGE   = 0x812F,
		MIRRORED_REPEAT = 0x8370
	};

	enum class Filter {
		NEAREST = 0x2600,
		LINEAR  = 0x2601
	};

	enum class ColorSpace {
		RGB = 0x1907,
		RGBA = 0x1908
	};

	struct TextureSpecification {
		ColorSpace colorSpace	= ColorSpace::RGB;

		Filter magFilter		= Filter::NEAREST;
		Filter minFilter		= Filter::NEAREST;

		Wrap sWrap				= Wrap::REPEAT;
		Wrap tWrap				= Wrap::REPEAT;

		unsigned int hTiles		= 1;
		unsigned int vTiles		= 1;
	};

	class melismaAPI Texture {
	public:
		Texture(const char *filename, TextureSpecification spec);
		Texture(const void *data, int width, int height, TextureSpecification spec);
		~Texture();

		void BindToSlot(unsigned int slot);

		int Width() const { return m_Width; }
		int Height() const { return m_Height; }

	public:
		static void BindContiguous(Texture *textures, unsigned int count);

	private:
		unsigned int m_RendererID;

		unsigned int m_Width;
		unsigned int m_Height;

		unsigned int m_hTiles;
		unsigned int m_vTiles;

		mlDeclareDebugName;
	};

}