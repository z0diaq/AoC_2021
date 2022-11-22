module;

//imports
#include <iostream>
#include <deque>

export module smoke;

export import :data;

//smoke => SEvent SEgments SEarch
export namespace smoke
{

	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool ProcessOne( const AoC::DataPtr& data ) override;
		virtual bool ProcessTwo( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:
		std::deque<Data::DataLine> m_heightmap;

		bool IsLowPoint( uint32_t column, uint32_t row ) const;
		uint32_t RiskLevel( uint32_t column, uint32_t row ) const;
		uint32_t Width( ) const;
		uint32_t Height( ) const;
		uint8_t Value( uint32_t column, uint32_t row ) const;
	};
}

using namespace smoke;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new smoke::Data( ) );
	m_haveDedicatedProcessing = true;
}

void
Result::Teardown( )
{
	m_data.reset( );
	m_heightmap.clear( );
}

bool
Result::ProcessOne( const AoC::DataPtr& data )
{
	m_heightmap.push_back( static_cast< smoke::Data* >( data.get( ))->m_dataLine );

	return true;//drop data, we used all
}

bool
Result::ProcessTwo( const AoC::DataPtr& data )
{
	return true;//drop data, we used all
}

uint64_t
Result::Finish( ) const
{
	uint64_t accumulated = 0;
	for( uint32_t row = 0; row < Height( ); ++row )
	{
		for( uint32_t column = 0; column < Width( ); ++column )
		{
			if( IsLowPoint( column, row ) )
				accumulated += RiskLevel( column, row );
		}
	}

	std::cout
		<< "result = "
		<< accumulated
		<< std::endl;

	return accumulated;
}

bool
Result::IsLowPoint( uint32_t column, uint32_t row ) const
{
	auto ourValue = Value( column, row );
	if( column > 0 && Value( column - 1, row ) <= ourValue )
		return false;
	if( column < ( Width( ) - 1 ) && Value( column + 1, row ) <= ourValue )
		return false;
	if( row > 0 && Value( column, row - 1 ) <= ourValue )
		return false;
	if( row < ( Height( ) - 1 ) && Value( column, row + 1 ) <= ourValue )
		return false;

	return true;
}

uint32_t
Result::RiskLevel( uint32_t column, uint32_t row ) const
{
	return Value( column, row ) + 1;
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
Result::Value( uint32_t column, uint32_t row ) const
{
	return m_heightmap[ row ][ column ];
}
