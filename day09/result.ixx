module;

//imports
#include <iostream>

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

		//stage 1
		uint64_t m_accumulated;
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
	m_accumulated = 0;
	m_haveDedicatedProcessing = true;
}

void
Result::Teardown( )
{
	m_data.reset( );
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
	std::cout
		<< "result = "
		<< m_accumulated
		<< std::endl;

	return m_accumulated;
}
