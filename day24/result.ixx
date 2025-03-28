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

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown( ) override
		{
			m_instructions.clear( );
		}

	private:
		//data
		std::vector<std::string> m_instructions;

		void ExtractDigitBlocks( );
	};
}
