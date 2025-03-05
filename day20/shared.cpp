import trench_map;

#include <bitset>
#include <ranges>
#include <algorithm>

using namespace trench_map;

void
Result::Init()
{
	m_inImage = false;
	m_enhanceAlgorithm.reserve( 512 );
	m_scanLineNumber = 0;
	m_bounds.m_minX = m_bounds.m_maxX = m_bounds.m_minY = m_bounds.m_maxY = 0;
}

void
Result::Teardown()
{
	m_enhanceAlgorithm.clear( );
	m_litPixelsSet.clear( );
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
				column >= _bounds.m_minX && column <= _bounds.m_maxX &&
				row >= _bounds.m_minY && row <= _bounds.m_maxY;

			// Use infinite state for pixels outside bounds
			const bool isLit = isInBounds ?
				( _image.count( { column, row } ) == 1U ) : _isInfiniteLit;

			areaBits[ bitNum-- ] = isLit;
		}
	}

	return areaBits.to_ulong( );
}

std::pair<LitPixelsSet, Bounds>
EnhanceImage( const LitPixelsSet& _image, const std::string& _algorithm, Bounds _bounds, bool& _infiniteIsLit )
{
	LitPixelsSet result{};

	// Process enhancement
	for( int row{ _bounds.m_minY - 1 }; row <= _bounds.m_maxY + 1; ++row )
	{
		for( int column{ _bounds.m_minX - 1 }; column <= _bounds.m_maxX + 1; ++column )
		{
			const auto indexFromArea = Area3x3( _image, _algorithm, _bounds, _infiniteIsLit, column, row );
			const bool markLit{ ( _algorithm[ indexFromArea ] == '#' ) };
			if( markLit )
				result.insert( { column, row } );
		}
	}

	// Expand bounds for possible new values
	--_bounds.m_minX;
	--_bounds.m_minY;
	++_bounds.m_maxX;
	++_bounds.m_maxY;

	// Update infinite pixel state for next enhancement
	if( !_infiniteIsLit )
		_infiniteIsLit = ( _algorithm[ 0 ] == '#' );
	else
		_infiniteIsLit = ( _algorithm[ 511 ] == '#' );

	// Lambda functions to check if a row or column is empty
	auto IsRowEmpty = [&result, &_bounds]( int y ) {
		return std::ranges::none_of(
			std::views::iota( _bounds.m_minX, _bounds.m_maxX + 1 ),
			[&result, y]( int x ) { return result.contains( { x, y } ); }
		);
		};

	auto IsColumnEmpty = [&result, &_bounds]( int x ) {
		return std::ranges::none_of(
			std::views::iota( _bounds.m_minY, _bounds.m_maxY + 1 ),
			[&result, x]( int y ) { return result.contains( { x, y } ); }
		);
		};

	// Trim empty rows and columns from all sides
	// From top
	while( _bounds.m_minY <= _bounds.m_maxY && IsRowEmpty( _bounds.m_minY ) )
		++_bounds.m_minY;

	// From bottom
	while( _bounds.m_maxY >= _bounds.m_minY && IsRowEmpty( _bounds.m_maxY ) )
		--_bounds.m_maxY;

	// From left
	while( _bounds.m_minX <= _bounds.m_maxX && IsColumnEmpty( _bounds.m_minX ) )
		++_bounds.m_minX;

	// From right
	while( _bounds.m_maxX >= _bounds.m_minX && IsColumnEmpty( _bounds.m_maxX ) )
		--_bounds.m_maxX;

	return { result, _bounds };
}
