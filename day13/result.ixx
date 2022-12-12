module;

#include <string>
#include <vector>

export module transparent_origami;

import AoC;

export namespace transparent_origami
{
	class Result : public AoC::Result
	{
	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::vector<std::string> m_sheet;

		//true if we have 'fold by' type of line - this info allows to break correctly in part 1
		bool Process( const std::string& data );
		void ReadPoint( const std::string& data );
		void ReadAndExecuteFoldOperation( const std::string& data );
		void ResizeLines( );
	};
}
