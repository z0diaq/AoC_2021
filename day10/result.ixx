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

		//shared
		std::string GetCompletionTextOrFirstInvalidCharacter( const std::string& line, char& invalidCar ) const;


		//part one section
		virtual uint64_t FinishPartOne( ) const;
		uint32_t LookupScore( char c ) const;
		uint32_t m_cummulativeSyntaxErrorScore;

		//part two section
		virtual uint64_t FinishPartTwo( ) const;
		uint64_t CompletionTextScore( const std::string& text ) const;

		std::deque<uint64_t> m_allScores;
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
	m_allScores.clear( );
}

bool
Result::ProcessOne( const AoC::DataPtr& data )
{
	char invalidChar;
	if( GetCompletionTextOrFirstInvalidCharacter( static_cast< syntax_scoring::Data *>( data.get( ))->m_line, invalidChar ).empty( ) )
	{
		m_cummulativeSyntaxErrorScore += LookupScore( invalidChar );
	}

	return true;//drop data, we used all
}

std::string
Result::GetCompletionTextOrFirstInvalidCharacter( const std::string& line, char& c ) const
{
	std::deque<char> stack;

	auto GetClosingChar = [ ]( char c ) -> char
	{
		if( c == '(' ) return ')';
		if( c == '[' ) return ']';
		if( c == '{' ) return '}';
		if( c == '<' ) return '>';

		throw std::logic_error( "Invalid character" );
	};

	auto firstInvalid = std::find_if( line.begin( ), line.end( ), [ &stack, GetClosingChar ]( char ch )
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
			if( stack.empty( ) || GetClosingChar( stack.back( ) ) != ch )
				return true;
			stack.pop_back( );
		}
	return false;
	} );
	
	std::string result;

	if( firstInvalid == line.end( ) )
	{
		while( false == stack.empty( ) )
		{
			result.push_back( GetClosingChar( stack.back( ) ) );
			stack.pop_back( );
		}
	}
	else
		c = *firstInvalid;

	return result;
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
	char invalidChar;
	const std::string line = static_cast< syntax_scoring::Data* >( data.get( ) )->m_line;
	const std::string completionText = GetCompletionTextOrFirstInvalidCharacter( line, invalidChar );
	if( false == completionText.empty( ) )
	{
		m_allScores.push_back( CompletionTextScore( completionText ) );
	}
	return true;//drop data, we used all
}

uint64_t
Result::CompletionTextScore( const std::string& text ) const
{
	auto GetCharValue = [ ]( char c ) -> uint64_t
	{
		switch( c )
		{
		case ')':
			return 1;
		case ']':
			return 2;
		case '}':
			return 3;
		case '>':
			return 4;
		default:
			throw std::logic_error( "Invalid character in CompletionTextScore::GetCharValue" );
		}
	};

	uint64_t score = 0;
	for( auto ch : text )
	{
		score = score * 5 + GetCharValue( ch );
	}

	return score;
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
	auto scoresCopy( m_allScores );
	auto middleElement = scoresCopy.begin( ) + scoresCopy.size( ) / 2;// 'There will always be an odd number of scores to consider'

	std::nth_element( scoresCopy.begin( ), middleElement, scoresCopy.end( ) );

	return *middleElement;
}