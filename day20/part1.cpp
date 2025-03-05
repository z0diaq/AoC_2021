import trench_map;

#include <string>
#include <stdexcept>

using namespace trench_map;

void
ProcessNextScanLine( LitPixelsSet& _litPixelsSet, const std::string& _data, int _scanLineNumber );

void
Result::ProcessOne( const std::string& data )
{
	if( m_inImage )
	{
		ProcessNextScanLine( m_litPixelsSet, data, m_scanLineNumber++ );
		m_bounds.m_maxX = std::max( m_bounds.m_maxX, static_cast< int >( data.length( ) ) );
		m_bounds.m_maxY = m_scanLineNumber;
	}
	else
	{
		if( data.empty( ) )
			m_inImage = true;
		else
			m_enhanceAlgorithm.append( data );
	}
}

std::pair<LitPixelsSet, Bounds>
EnhanceImage( const LitPixelsSet& _image, const std::string& _algorithm, Bounds _bounds, bool& _infiniteIsLit );

std::string
Result::FinishPartOne( )
{
	if( m_enhanceAlgorithm.length( ) != 512 )
		throw std::logic_error( "Enhance algorithm must have 512 columns" );

	bool infiniteIsLit{ false };

	auto [newImage, newBounds] = EnhanceImage( m_litPixelsSet, m_enhanceAlgorithm, m_bounds, infiniteIsLit );
	auto [finalImage, finalBounds] = EnhanceImage( newImage, m_enhanceAlgorithm, newBounds, infiniteIsLit );

	return std::to_string( finalImage.size( ) );
}

void
ProcessNextScanLine( LitPixelsSet& _litPixelsSet, const std::string& _data, int _scanLineNumber )
{
	for( int x{ 0 }; x != static_cast< int >( _data.length( ) ); ++x )
		if( _data[ x ] == '#' )
			_litPixelsSet.emplace( Pixel{ x, _scanLineNumber } );
}
