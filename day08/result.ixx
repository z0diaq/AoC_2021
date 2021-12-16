module;

#include <iostream>
#include <deque>
#include <array>
#include <algorithm>
#include <numeric>

export module sesese;

export import :data;

export namespace sesese
{

	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool Process( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:
		unsigned int m_foundCount;
	};
}

using namespace sesese;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new sesese::Data( ) );
	m_foundCount = 0;
}

void
Result::Teardown( )
{
	m_data.reset( );
}

bool
Result::Process( const AoC::DataPtr& data )
{
	const Data* ourData = dynamic_cast< const Data* >( data.get( ) );

	if( false == IsPartTwo( ) )
	{
		m_foundCount += std::count_if(
			ourData->m_testData.begin( ),
			ourData->m_testData.end( ),
			[ ]( const std::string& segments )
		{
			switch( segments.length( ) )
			{
			case 2://1
			case 3://7
			case 4://4
			case 7://9
				return true;
			default:
				return false;
			}
		} );
	}

	return true;
}

uint64_t
Result::Finish( ) const
{
	uint64_t computedValue = m_foundCount;

	std::cout
		<< "result = "
		<< computedValue
		<< std::endl;

	return computedValue;
}
