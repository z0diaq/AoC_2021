module;

#include <memory>

export module snailfish:node;

export namespace snailfish
{
	class Node {
	private:
		int m_value{ 0 };
		std::unique_ptr<Node> m_left, m_right;

	public:
		Node( ) = default;
		Node( int value ) : m_value( value ) { }

		int Value( ) const {
			return m_value;
		}

		bool IsRegular( ) const {
			return !m_left && !m_right;
		}

		void SetValue( int v ) {
			m_value = v;
		}

		void SetChildren( std::unique_ptr<Node> l, std::unique_ptr<Node> r ) {
			m_left = std::move( l );
			m_right = std::move( r );
		}
	};
}
