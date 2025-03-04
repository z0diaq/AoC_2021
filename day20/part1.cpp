import trench_map;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

#include <iostream>

//containers
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <array>
#include <bitset>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace trench_map;

void
ProcessNextScanLine( LitPixelsSet& _litPixelsSet, const std::string& _data, int _scanLineNumber );

void
Result::ProcessOne( const std::string& data )
{
	if( m_inImage )
	{
		ProcessNextScanLine( m_litPixelsSet, data, m_scanLineNumber++ );
		m_bounds[ MAX_X ] = std::max( m_bounds[ MAX_X ], static_cast< int >( data.length( ) ) );
		m_bounds[ MAX_Y ] = m_scanLineNumber;
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
EnhanceImage( const LitPixelsSet& _image, const std::string& _algorithm, bool& _infiniteIsLit );

void DumpImage( const LitPixelsSet& _image, const Bounds& _bounds );

std::string
Result::FinishPartOne( )
{
	bool infiniteIsLit{ false };

	auto [newImage, newBounds] = EnhanceImage( m_litPixelsSet, m_enhanceAlgorithm, infiniteIsLit );
	std::cout << "\tAfter 1st enhancement:" << std::endl;
	DumpImage( newImage, newBounds );

	auto [finalImage, finalBounds] = EnhanceImage( newImage, m_enhanceAlgorithm, infiniteIsLit );
	std::cout << "\tAfter 2nd enhancement:" << std::endl;
	DumpImage( finalImage, finalBounds );

	return std::to_string( finalImage.size( ) );
}

void
ProcessNextScanLine( LitPixelsSet& _litPixelsSet, const std::string& _data, int _scanLineNumber )
{
	for( int x{ 0 }; x != static_cast< int >( _data.length( ) ); ++x )
		if( _data[ x ] == '#' )
			_litPixelsSet.emplace( Pixel{ x, _scanLineNumber } );
}

unsigned long
Area3x3( const LitPixelsSet& _image, const std::string& _algorithm, const Bounds& _bounds, const bool _isInfiniteLit, const int _column, const int _row )
{
	std::bitset<9> areaBits{};
	size_t bitNum{ 8 }; // Start with most significant bit

	for( int row{ _row - 1 }; row <= _row + 1; ++row )
	{
		for( int column{ _column - 1 }; column <= _column + 1; ++column )
		{
			const bool isInBounds =
				column >= _bounds[ MIN_X ] && column < _bounds[ MAX_X ] &&
				row >= _bounds[ MIN_Y ] && row < _bounds[ MAX_Y ];

			// Use infinite state for pixels outside bounds
			const bool isLit = isInBounds ?
				( _image.count( { column, row } ) == 1U ) : _isInfiniteLit;

			areaBits[ bitNum-- ] = isLit;
		}
	}

	return areaBits.to_ulong( );
}

std::pair<LitPixelsSet, Bounds>
EnhanceImage( const LitPixelsSet& _image, const std::string& _algorithm, bool& _infiniteIsLit )
{
	Bounds bounds;
	bounds[ MIN_X ] = bounds[ MAX_X ] = _image.begin( )->first;
	bounds[ MIN_Y ] = bounds[ MAX_Y ] = _image.begin( )->second;
	for( const auto& pt : _image )
	{
		bounds[ MIN_X ] = std::min( bounds[ MIN_X ], pt.first );
		bounds[ MIN_Y ] = std::min( bounds[ MIN_Y ], pt.second );
		bounds[ MAX_X ] = std::max( bounds[ MAX_X ], pt.first );
		bounds[ MAX_Y ] = std::max( bounds[ MAX_Y ], pt.second );
	}


	// Expand bounds
	--bounds[ MIN_X ];
	--bounds[ MIN_Y ];
	++bounds[ MAX_X ];
	++bounds[ MAX_Y ];

	LitPixelsSet result{};

	static bool firstRow{ true };

	// Process enhancement
	for( int row{ bounds[ MIN_Y ] }; row <= bounds[ MAX_Y ]; ++row )
	{
		for( int column{ bounds[ MIN_X ] }; column <= bounds[ MAX_X ]; ++column )
		{
			const auto indexFromArea = Area3x3( _image, _algorithm, bounds, _infiniteIsLit, column, row );
			const bool markLit{ ( _algorithm[ indexFromArea ] == '#' ) };
			if( markLit )
				result.insert( { column, row } );
			if( firstRow )
				std::cout << "col: " << column << " => index: " << indexFromArea << " " << ( markLit ? "#" : "." ) << std::endl;
		}
		firstRow = false;
	}

	// Update infinite pixel state for next enhancement
	if( !_infiniteIsLit )
		_infiniteIsLit = ( _algorithm[ 0 ] == '#' );
	else
		_infiniteIsLit = ( _algorithm[ 511 ] == '#' );

	return { result, bounds };
}

void
DumpImage( const LitPixelsSet& _image, const Bounds& _bounds )
{
	for( int row{ _bounds[ MIN_Y ] }; row != _bounds[ MAX_Y ]; ++row )
	{
		for( int column{ _bounds[ MIN_X ] }; column != _bounds[ MAX_X ]; ++column )
		{
			if( _image.count( { column, row } ) )
				std::cout << "#";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}
}
