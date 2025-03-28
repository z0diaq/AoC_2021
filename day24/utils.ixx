export module alu:utils;

import :result;

import <regex>;
import <numeric>;

namespace alu
{
	void Result::ExtractDigitBlocks( )
	{
		// Find all block start positions (marked by "inp w")
		auto blockStarts = [this]( ) {
			std::vector<size_t> starts;
			for( size_t i = 0; i < m_instructions.size( ); ++i )
			{
				if( m_instructions[ i ] == "inp w" )
					starts.push_back( i );
			}
			return starts;
			}( );

		// Create regular expressions for extracting parameters
		const std::regex reDiv( "div z (-?\\d+)" );
		const std::regex reCheck( "add x (-?\\d+)" );
		const std::regex reAdd( "add y (-?\\d+)" );

	}
}
