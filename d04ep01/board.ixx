module;

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <algorithm>

export module giant_squid:data.board;

export import AoC;

export namespace giant_squid
{
    typedef std::array<unsigned int, 25> BoardData;
    constexpr unsigned int MARK = static_cast< unsigned int >( -1 );

    class Board
    {
    public:
        void Push( unsigned int number );
        bool IsFilled( ) const;
        void MarkNumber( unsigned int number );
        bool Bingo( unsigned int& result ) const;

        void Reset( );

    private:
        bool IsMarked( size_t col, size_t row ) const;

        BoardData    m_data;
        unsigned int m_size = 0;
        unsigned int m_lastMarkedNumber = 0;
    };
}

void
giant_squid::Board::Push( unsigned int number )
{
    if( m_size == 25 )
        throw std::exception( "Reached array limit, did You forget to consume data ?" );
    m_data[ m_size++ ] = number;
}

bool
giant_squid::Board::IsFilled( ) const
{
    return m_size == 25;
}

void
giant_squid::Board::MarkNumber( unsigned int number )
{
    std::for_each(
        m_data.begin( ),
        m_data.end( ),
        [ number ]( unsigned int& value ) -> void
    {
        if( value == number )
            value = MARK;
    } );

    m_lastMarkedNumber = number;
}

bool
giant_squid::Board::Bingo( unsigned int& result ) const
{
    result = 0;
    bool isBingo = false;
    for( size_t row = 0; row < 5; ++row )
    {
        size_t
            marksHorizontal = 0,
            marksVertical = 0;
        for( size_t col = 0; col < 5; ++col )
        {
            marksHorizontal += this->IsMarked( col, row );
            marksVertical += this->IsMarked( row, col );

            if( false == this->IsMarked( col, row ) )
                result += m_data.at( row * 5 + col );
        }
        if( marksHorizontal == 5 || marksVertical == 5 )
            isBingo = true;
    }

    result *= m_lastMarkedNumber;
    return isBingo;
}

bool
giant_squid::Board::IsMarked( size_t col, size_t row ) const
{
    return m_data.at( row * 5 + col ) == MARK;
}

void
giant_squid::Board::Reset( )
{
    m_data.fill( 0 );
    m_size = 0;
    m_lastMarkedNumber = 0;
}
