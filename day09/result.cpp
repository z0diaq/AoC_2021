import smoke;

#include <queue>
#include <iostream>

using namespace smoke;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new smoke::Data( ) );
	m_haveDedicatedProcessing = false;
}

void
Result::Teardown( )
{
	m_data.reset( );
	m_heightmap.clear( );
}

bool
Result::ProcessGeneral( const AoC::DataPtr& data )
{
	m_heightmap.push_back( static_cast< smoke::Data* >( data.get( ) )->m_dataLine );

	return true;//drop data, we used all
}

uint64_t
Result::Finish( ) const
{
	uint64_t processingResult = IsPartOne( ) ? FinishPartOne( ) : FinishPartTwo( );

	std::cout
		<< "result = "
		<< processingResult
		<< std::endl;

	return processingResult;
}

uint32_t
Result::FinishPartOne( ) const
{
	uint32_t processingResult = 0;
	PartTwoSolver data( this );

	std::priority_queue<uint32_t> stageTwoBasinSizes;
	for( uint32_t row = 0; row < Height( ); ++row )
	{
		for( uint32_t column = 0; column < Width( ); ++column )
		{
			if( IsLowPoint( { column, row } ) )
			{
				processingResult += RiskLevel( { column, row } );
			}
		}
	}

	return processingResult;
}

uint32_t
Result::FinishPartTwo( ) const
{
	PartTwoSolver data( this );

	std::priority_queue<uint32_t> stageTwoBasinSizes;
	for( uint32_t row = 0; row < Height( ); ++row )
	{
		for( uint32_t column = 0; column < Width( ); ++column )
		{
			if( IsLowPoint( { column, row } ) )
			{
				data.AnalyzeBasin( { column, row } );
			}
		}
	}

	return data.ComputeResult( );
}

bool
Result::IsLowPoint( const Point& point ) const
{
	auto ourValue = Value( point );
	if( point.first > 0 && Value( { point.first - 1, point.second } ) <= ourValue )
		return false;
	if( point.first < ( Width( ) - 1 ) && Value( { point.first + 1, point.second } ) <= ourValue )
		return false;
	if( point.second > 0 && Value( { point.first, point.second - 1 } ) <= ourValue )
		return false;
	if( point.second < ( Height( ) - 1 ) && Value( { point.first, point.second + 1 } ) <= ourValue )
		return false;

	return true;
}

uint32_t
Result::RiskLevel( const Point& point ) const
{
	return Value( point ) + 1;
}

uint32_t
Result::Width( ) const
{
	return static_cast< uint32_t >( m_heightmap.front( ).size( ) );
}

uint32_t
Result::Height( ) const
{
	return static_cast< uint32_t >( m_heightmap.size( ) );
}

uint8_t
Result::Value( const Point& point ) const
{
	return m_heightmap[ point.second ][ point.first ];
}
