export module alu:result;

import :types;

import AoC;

import <string>;
import <vector>;

export namespace alu
{
	class Result : public AoC::Result
	{

	public:
		Result( )
		{
		}

	protected:
		virtual void Init( ) override
		{
		}

		virtual void ProcessOne( const std::string& data ) override
		{
			m_instructions.push_back( data );
		}

		virtual std::string FinishPartOne( ) override
		{
			DigitsMap digits = ExtractDigitsMap( );

			std::string maxModelNumber;
			for( int i = 0; i < 14; i++ )
				maxModelNumber += std::to_string( digits[ i ].second );

			return maxModelNumber;
		}


		virtual void ProcessTwo( const std::string& data ) override
		{
			ProcessOne( data );
		}

		virtual std::string FinishPartTwo( ) override
		{
			DigitsMap digits = ExtractDigitsMap( );

			std::string minModelNumber;
			for( int i = 0; i < 14; i++ )
				minModelNumber += std::to_string( digits[ i ].first );

			return minModelNumber;
		}

		virtual void Teardown( ) override
		{
			m_instructions.clear( );
		}

	private:
		//data
		std::vector<std::string> m_instructions;

		DigitsMap ExtractDigitsMap( );
	};
}
