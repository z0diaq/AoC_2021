import snailfish;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

//containers
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <array>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace snailfish;

void
Result::ProcessOne( const std::string& data )
{
	m_numbers.push_back( data );
}

std::string
Result::FinishPartOne( )
{
	std::reverse( m_numbers.begin( ), m_numbers.end( ) );
	auto root{ Parse( nullptr, m_numbers.back( ) ) };
	m_numbers.pop_back( );

	while( false == m_numbers.empty( ) )
	{
		root = Add( std::move( root ), Parse( nullptr, m_numbers.back( ) ) );
		m_numbers.pop_back( );
	}

	return std::to_string( Magnitude( root ) );
}
