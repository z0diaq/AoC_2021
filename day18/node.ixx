module;

#include <memory>

export module snailfish:node;

export namespace snailfish
{
	struct Node
	{
		Node* m_parent;// view type
		int m_value{ 0 };
		std::unique_ptr<Node> m_left;
		std::unique_ptr<Node> m_right;

		Node( Node* parent ) : m_parent( parent ) { }
		Node( Node *parent, int value ) : m_parent( parent ), m_value( value ) { }

		bool IsRegular( ) const {
			return !m_left && !m_right;
		}
	};
}
