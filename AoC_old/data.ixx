module;

#include <string>
#include <memory>

export module AoC:data;

export namespace AoC
{
	struct Data
	{
		virtual void Process( const std::string& line ) = 0;
		virtual void Reset( ) { }
	};

	typedef std::unique_ptr<Data> DataPtr;
}