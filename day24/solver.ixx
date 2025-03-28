export module alu:solver;

import :result;
import :types;

import <string>;

using namespace alu;

void
Result::ProcessOne( const std::string& data )
{
	m_instructions.push_back( data );
}

std::string
Result::FinishPartOne( )
{
	ExtractDigitBlocks( );
	return std::to_string( 0 );
}

void
Result::ProcessTwo( const std::string& data )
{
}

std::string
Result::FinishPartTwo( )
{
	return std::to_string( 0 );
}
