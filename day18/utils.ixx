module;

#include <memory>
#include <string>
#include <algorithm>

export module snailfish:utils;

import :node;

export namespace snailfish
{
	// Parse a snailfish number from string
	std::unique_ptr<Node> parse( const std::string& str ) {
		if( std::all_of( str.begin( ), str.end( ), ::isdigit ) ) {
			return std::make_unique<Node>( std::stoi( str ) );
		}

		int commaPosition = 0;
		int depth = 0;
		for( int i = 1; i < str.size( ) - 1; ++i ) {
			if( str[ i ] == '[' ) depth++;
			if( str[ i ] == ']' ) depth--;
			if( str[ i ] == ',' && depth == 1 ) {
				commaPosition = i;
				break;
			}
		}

		auto root = std::make_unique<Node>( );
		auto left = parse( str.substr( 1, commaPosition - 1 ) );
		auto right = parse( str.substr( commaPosition + 1, str.size( ) - commaPosition - 2 ) );
		root->SetChildren( std::move( left ), std::move( right ) );
		return root;
	}
}
