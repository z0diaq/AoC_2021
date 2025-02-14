module;

#include <memory>
#include <string>
#include <algorithm>

export module snailfish:utils;

import :node;

export namespace snailfish
{
	// Parse a snailfish number from string
	std::unique_ptr<Node> Parse( Node* parent, const std::string& str ) {
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

		auto root = std::make_unique<Node>( parent );
		root->m_left = Parse( root.get( ), str.substr( 1, commaPosition - 1 ) );
		root->m_right = Parse( root.get( ), str.substr( commaPosition + 1, str.size( ) - commaPosition - 2 ) );
		return root;
	}

	Node* FindPreviousLeaf( Node* node );
	Node* FindNextLeaf( Node* node );

	bool Explode( std::unique_ptr<Node>& node, int depth = 0 ) {
		if( !node ) return false;

		if( node->IsRegular( ) ) return false;

		if( depth >= 4 ) {
			if( node->m_left && node->m_right )
			{
				Node* previousLeaf = FindPreviousLeaf( node );
				Node* nextLeaf = FindNextLeaf( node );

				if( previousLeaf )
					previousLeaf->m_value += node->m_left->m_value;
				if( nextLeaf )
					nextLeaf->m_value += node->m_right->m_value;

				node->m_value = 0;
				node->m_left.reset( );
				node->m_right.reset( );

				return true;
			}
		}

		return Explode( node->m_left, depth + 1 ) ||
			Explode( node->m_right, depth + 1 );
	}
}
