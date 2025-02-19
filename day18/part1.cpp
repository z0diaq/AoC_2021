import snailfish;

#include <string>
#include <memory>

using namespace snailfish;

void
Result::ProcessOne( const std::string& data )
{
	m_numbers.push_back( data );
}

std::string
Result::FinishPartOne( )
{
	auto result{ std::make_unique<Node>( ) };
	for( const auto& number : m_numbers )
		result = Add( std::move( result ), Parse( number ) );

	return std::to_string( Magnitude( result ) );
}
