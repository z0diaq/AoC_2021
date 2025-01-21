module;

#include <string>
#include <list>
#include <map>

export module extended_polymerization;

import AoC;

export namespace extended_polymerization
{
	using CharList = std::list<char>;
	using PairInsertionRulesMap = std::map<char, std::map<char, char> >;

	class Result : public AoC::Result
	{

	public:
		Result();

	protected:

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		CharList m_template;
		PairInsertionRulesMap m_pairInsertionRules;
	};
}
