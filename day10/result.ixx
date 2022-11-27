module;

//imports
#include <iostream>
#include <deque>
#include <algorithm>

export module syntax_scoring;

export import :data;

//smoke => SEvent SEgments SEarch
export namespace syntax_scoring
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

		//part one section
		virtual uint64_t FinishPartOne( ) const;
		bool HasIllegalCharacter( const std::string& line, char& c ) const;
		uint32_t LookupScore( char c ) const;
		uint32_t m_cummulativeSyntaxErrorScore;

		//part two section
		virtual uint64_t FinishPartTwo( ) const;
	};
}

using namespace syntax_scoring;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new syntax_scoring::Data( ) );
	m_haveDedicatedProcessing = true;
	m_cummulativeSyntaxErrorScore = 0;
}

void
Result::Teardown( )
{
	m_data.reset( );
}

bool
Result::ProcessOne( const AoC::DataPtr& data )
{
	char invalidChar;
	if( HasIllegalCharacter( static_cast< syntax_scoring::Data *>( data.get( ))->m_line, invalidChar ) )
	{
		m_cummulativeSyntaxErrorScore += LookupScore( invalidChar );
	}

	return true;//drop data, we used all
}

bool
Result::HasIllegalCharacter( const std::string& line, char& c ) const
{
	std::deque<char> stack;

	auto IsClosingChar = [ ]( char left, char right ) -> bool
	{
		if( left == '(' && right == ')' ) return true;
		if( left == '[' && right == ']' ) return true;
		if( left == '{' && right == '}' ) return true;
		if( left == '<' && right == '>' ) return true;

		return false;
	};

	auto firstInvalid = std::find_if( line.begin( ), line.end( ), [ &stack, IsClosingChar ]( char ch )
	{
		switch( ch )
		{
		case '(':
		case '[':
		case '{':
		case '<':
			stack.push_back( ch );
			break;
		case ')':
		case ']':
		case '}':
		case '>':
			if( stack.empty( ) || false == IsClosingChar( stack.back( ), ch ) )
				return true;
			stack.pop_back( );
		}
	return false;
	} );
	
	if( firstInvalid == line.end( ) )
		return false;

	c = *firstInvalid;
	return true;
}

uint32_t
Result::LookupScore( char c ) const
{
	switch( c )
	{
	case ')':
		return 3;
	case ']':
		return 57;
	case '}':
		return 1197;
	case '>':
		return 25137;
	default:
		throw std::logic_error( "Unexpected value" );
	}
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
	return m_cummulativeSyntaxErrorScore;
}

uint64_t
Result::FinishPartTwo( ) const
{
	return 0;
}