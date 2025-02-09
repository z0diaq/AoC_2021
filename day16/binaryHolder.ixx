module;

#include <string>

export module packet_decoder:binary_holder;

export namespace packet_decoder
{
	class BinaryHolder
	{
		std::string m_binaryData;
		size_t m_currentPosition;

	public:
		BinaryHolder( const std::string& binaryData );

		unsigned int GetNextChunk( size_t bitsCount );

		std::string GetNextStringChunk( size_t bitsCount );

		void AdjustPadding( );

		unsigned int CurrentPosition( ) const;
	};
};
