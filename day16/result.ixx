module;

#include <string>

export module packet_decoder;

export import :binary_holder;
export import :utils;

import AoC;

export namespace packet_decoder
{
	class Result : public AoC::Result
	{

	public:
		Result( ) = default;

	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::string m_packet;
	};
}
