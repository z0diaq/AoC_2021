import trench_map;

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
EnhanceImage( const LitPixelsSet& _image, const std::string& _algorithm, Bounds _bounds, bool& _infiniteIsLit );


std::string
Result::FinishPartOne( )
{
	bool infiniteIsLit{ false };
	auto [newImage, newBounds] = EnhanceImage( m_litPixelsSet, m_enhanceAlgorithm, m_bounds, infiniteIsLit );
	auto [finalImage, _] = EnhanceImage( newImage, m_enhanceAlgorithm, newBounds, infiniteIsLit );
	return std::to_string( finalImage.size( ) );
}

void
ProcessNextScanLine( LitPixelsSet& _litPixelsSet, const std::string& _data, int _scanLineNumber )
{
	for( int x{ 0 }; x != static_cast< int >( _data.length( ) ); ++x )
		if( _data[ x ] == '#' )
			_litPixelsSet.emplace( Pixel{ x, _scanLineNumber } );
}

std::pair<LitPixelsSet, Bounds>
EnhanceImage( const LitPixelsSet& _image, const std::string& _algorithm, Bounds _bounds, bool& _infiniteIsLit )
{
	// Expand bounds
	--_bounds[ MIN_X ];
	--_bounds[ MIN_Y ];
	++_bounds[ MAX_X ];
	++_bounds[ MAX_Y ];

	LitPixelsSet result{};

	auto area3x3 = [&_image, &_bounds, _infiniteIsLit]( int _column, int _row ) -> unsigned long
		{
			std::bitset<9> areaBits{};
			size_t bitNum{ 8 }; // Start with most significant bit

			for( int row{ _row - 1 }; row <= _row + 1; ++row )
			{
				for( int column{ _column - 1 }; column <= _column + 1; ++column )
				{
					bool isInBounds =
						column >= _bounds[ MIN_X ] && column < _bounds[ MAX_X ] &&
						row >= _bounds[ MIN_Y ] && row < _bounds[ MAX_Y ];

					// Use infinite state for pixels outside bounds
					bool isLit = isInBounds ?
						( _image.count( { column, row } ) == 1U ) : _infiniteIsLit;

					areaBits[ bitNum-- ] = isLit;
				}
			}

			return areaBits.to_ulong( );
		};

	// Process enhancement
	for( int column = _bounds[ MIN_X ]; column < _bounds[ MAX_X ]; ++column )
	{
		for( int row{ _bounds[ MIN_Y ] }; row < _bounds[ MAX_Y ]; ++row )
		{
			const auto indexFromArea = area3x3( column, row );
			if( _algorithm[ indexFromArea ] == '#' )
				result.insert( { column, row } );
		}
	}

	// Update infinite pixel state for next enhancement
	if( !_infiniteIsLit )
		_infiniteIsLit = ( _algorithm[ 0 ] == '#' );
	else
		_infiniteIsLit = ( _algorithm[ 511 ] == '#' );

	return { result, _bounds };
}
