module;

#include <memory>
#include <string>
#include <algorithm>

export module snailfish:utils;

import :node;

export namespace snailfish
{
	// Parse a snailfish number from string
	std::unique_ptr<Node> Parse( const std::string& str, Node* parent = nullptr ) {
		if( std::all_of( str.begin( ), str.end( ), ::isdigit ) ) {
			return std::make_unique<Node>( parent, std::stoi( str ) );
		}

		int commaPosition = 0;
		int depth = 0;
		for( int i = 0; i < str.size( ) - 1; ++i ) {
			if( str[ i ] == '[' ) depth++;
			if( str[ i ] == ']' ) depth--;
			if( str[ i ] == ',' && depth == 1 ) {
				commaPosition = i;
				break;
			}
		}

		auto root = std::make_unique<Node>( parent );
		root->m_left = Parse( str.substr( 1, commaPosition - 1 ), root.get( ) );
		root->m_right = Parse( str.substr( commaPosition + 1, str.size( ) - commaPosition - 2 ), root.get( ) );
		return root;
	}

	std::string Format( Node* node )
	{
		if( !node )
			return "";
		else
		{
			if( node->IsLeaf( ) )
				return std::to_string( node->m_value );
			else
				return std::string( "[" ) + Format( node->m_left.get( ) ) + "," + Format( node->m_right.get( ) ) + "]";
		}
	}

	Node* FindPreviousLeaf( Node* node );
	Node* FindNextLeaf( Node* node );

	bool Explode( std::unique_ptr<Node>& node, int depth = 0 ) {
		if( !node ) return false;

		if( node->CanExplode( depth ) )
		{
			Node* previousLeaf{ FindPreviousLeaf( node.get( ) ) };
			Node* nextLeaf{ FindNextLeaf( node.get( ) ) };

			if( previousLeaf )
				previousLeaf->m_value += node->m_left->m_value;

			if( nextLeaf )
				nextLeaf->m_value += node->m_right->m_value;

			node->m_value = 0;
			node->m_left.reset( );
			node->m_right.reset( );

			return true;
		}

		return Explode( node->m_left, depth + 1 ) ||
			Explode( node->m_right, depth + 1 );
	}

	Node* FindPreviousLeaf( Node* node )
	{
		// go up as long as we came from left side or we reached top
		while( true )
		{
			auto sourceNode{ node };
			node = node->m_parent;
			if( !node )
				return nullptr;

			if( node->m_left )
			{
				if( node->m_left.get( ) == sourceNode )
					continue;
				else
					break;
			}
		}

		node = node->m_left.get( );
		while( node->m_right )
			node = node->m_right.get( );
		return node;
	}

	Node* FindNextLeaf( Node* node )
	{
		// go up as long as we came from right side or we reached top
		while( true )
		{
			auto sourceNode{ node };
			node = node->m_parent;
			if( !node )
				return nullptr;

			if( node->m_right )
			{
				if( node->m_right.get( ) == sourceNode )
					continue;
				else
					break;
			}
		}

		node = node->m_right.get( );
		while( node->m_left )
			node = node->m_left.get( );
		return node;
	}

	bool Split( std::unique_ptr<Node>& node ) {
		if( !node ) return false;

		if( node->IsLeaf( ) ) {
			if( node->m_value >= 10 ) {
				int val = node->m_value;
				node->m_left = std::make_unique<Node>( node.get( ), val / 2 );
				node->m_right = std::make_unique<Node>( node.get( ), ( val + 1 ) / 2 );
				node->m_value = 0;

				return true;
			}
			return false;
		}

		return Split( node->m_left ) || Split( node->m_right );
	}

	void Reduce( std::unique_ptr<Node>& root, bool once = false ) {
		bool reduced;
		do {
			reduced = Explode( root ) || Split( root );
			if( once )
				return;
		} while( reduced );
	}

	int Magnitude( const std::unique_ptr<Node>& root ) {
		if( !root ) return 0;

		if( root->IsLeaf( ) ) {
			return root->m_value;
		}

		return 3 * Magnitude( root->m_left ) +
			2 * Magnitude( root->m_right );
	}

	std::unique_ptr<Node> Add( std::unique_ptr<Node>&& left, std::unique_ptr<Node>&& right )
	{
		auto result = std::make_unique<Node>( nullptr, 0 );
		result->m_left = std::move( left );
		result->m_left->m_parent = result.get( );
		result->m_right = std::move( right );
		result->m_right->m_parent = result.get( );

		Reduce( result );

		return result;
	}
}
