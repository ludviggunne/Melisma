#pragma once

namespace melisma{

	enum class AttributeType {
		FLOAT			= 0x1406,
		UNSIGNED_INT	= 0x1405,
		UNSIGNED_BYTE	= 0x1401
	};

	struct VertexAttribute {
		VertexAttribute(AttributeType type, unsigned int size) : Type(type), Size(size), m_TypeSize(0)
		{
			switch (type) {
			case AttributeType::FLOAT:
				m_TypeSize = 4;
				break;

			case AttributeType::UNSIGNED_INT:
				m_TypeSize = 4;
				break;

			case AttributeType::UNSIGNED_BYTE:
				m_TypeSize = 1;
				break;

			default:
				m_TypeSize = 1;
				break;
			}
		}

		AttributeType Type;
		unsigned int Size;

	private:
		unsigned int m_TypeSize;
		friend class VertexBufferLayout;
	};

}