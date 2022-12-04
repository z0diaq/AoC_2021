module;

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

#include <boost/algorithm/string/replace.hpp>

export module AoC:fs_helpers;

export namespace AoC
{
	namespace fs = std::filesystem;
	/*
	check expected locations for specified file:
	- current working directory - mostly different than location of executable
	- parent dir
	- parent dir \ secret \ tag
	- parent dir \ parent dir \ tag
	- parent dir \ parent dir \ tag \ secret
	*/
	bool
	FindFileInPredefinedLocations( const std::string& filename, fs::path& foundPath, const std::string& dataTag )
	{
		auto cwd = fs::current_path( );
		foundPath = cwd / filename;
		if( fs::exists( foundPath ) )
			return true;

		cwd = cwd.parent_path( );
		foundPath = cwd / filename;
		if( fs::exists( foundPath ) )
			return true;

		foundPath = cwd / "secret" / dataTag / filename;
		if( fs::exists( foundPath ) )
			return true;

		cwd = cwd.parent_path( );
		foundPath = cwd / filename;
		if( fs::exists( foundPath ) )
			return true;

		foundPath = cwd / "secret" / dataTag / filename;
		if( fs::exists( foundPath ) )
			return true;

		return false;
	}

	std::string ReadFileContents( const fs::path& path )
	{
		std::ifstream file( path, std::ios::in | std::ios::binary );
		const auto fileSize = fs::file_size( path );

		std::string result( fileSize, '\0' );

		file.read( result.data( ), fileSize );

		return result;
	}

	enum class DataType
	{
		INPUT,
		RESULT_PART_1,
		RESULT_PART_2
	};

	fs::path GetPathVariant( const fs::path& source, DataType requestedVariant )
	{
		auto newSourceStem = source.stem( ).string( );
		if( requestedVariant == DataType::RESULT_PART_1 )
			newSourceStem.append( "_result_part1" );
		else if( requestedVariant == DataType::RESULT_PART_2 )
			newSourceStem.append( "_result_part2" );
		std::string sourcePath( source.string( ) );

		boost::replace_last( sourcePath, source.stem( ).string( ), newSourceStem );

		return sourcePath;
	}
}