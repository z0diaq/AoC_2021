module;

#include <string>

export module AoC:data;

export namespace AoC
{
	struct Data
	{
		virtual void Process( const std::string& line ) = 0;
	};
}