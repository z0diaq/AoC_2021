module;

//imports
#include <iostream>

export module aoc_template;

export import :data;

//smoke => SEvent SEgments SEarch
export namespace aoc_template
{
	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool ProcessGeneral( const AoC::DataPtr& data ) override;
		virtual bool ProcessOne( const AoC::DataPtr& data ) override;
		virtual bool ProcessTwo( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:

		//part one section
		virtual uint64_t FinishPartOne( ) const;

		//part two section
		virtual uint64_t FinishPartTwo( ) const;
	};
}

using namespace aoc_template;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new aoc_template::Data( ) );
	m_haveDedicatedProcessing = true;
}

void
Result::Teardown( )
{
	m_data.reset( );
}

bool
Result::ProcessGeneral( const AoC::DataPtr& data )
{
	return true;//drop data, we used all
}

bool
Result::ProcessOne( const AoC::DataPtr& data )
{
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
	const uint64_t result = IsPartOne( ) ? FinishPartOne( ) : FinishPartTwo( );
	std::cout
		<< "result = "
		<< result
		<< std::endl;

	return result;
}

uint64_t
Result::FinishPartOne( ) const
{
	return 0;
}

uint64_t
Result::FinishPartTwo( ) const
{
	return 0;
}