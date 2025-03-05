import trench_map;

//leave what is needed
#include <string>
#include <stdexcept>

using namespace trench_map;

void
Result::ProcessTwo(const std::string& data)
{
	ProcessOne( data );
}

extern std::pair<LitPixelsSet, Bounds>
EnhanceImage( const LitPixelsSet& _image, const std::string& _algorithm, Bounds _bounds, bool& _infiniteIsLit );

std::string
Result::FinishPartTwo()
{
	if( m_enhanceAlgorithm.length( ) != 512 )
		throw std::logic_error( "Enhance algorithm must have 512 columns" );

	bool infiniteIsLit{ false };

	auto image{ m_litPixelsSet };
	auto bounds{ m_bounds };

	for( int iteration{ 0 }; iteration != 50; ++iteration )
	{
		auto [newImage, newBounds] = EnhanceImage( image, m_enhanceAlgorithm, bounds, infiniteIsLit );
		image = std::move( newImage );
		bounds = newBounds;
	}

	return std::to_string( image.size( ) );
}