module;

#include <iostream>

export module AoC;

export import :data;
import :input;

export namespace AoC
{
    class Result
    {

    public:
        Result( );
        virtual ~Result( );

        virtual void Init( ) = 0;
        virtual void Process( const Data* data ) = 0;
        virtual void Finish( ) const = 0;
        virtual void Teardown( ) = 0;

        virtual int Execute( );

    protected:
        Data* m_data;
    };
}

AoC::Result::Result( ) :
    m_data( nullptr )
{
}

AoC::Result::~Result( )
{
    delete m_data;
}

int
AoC::Result::Execute( )
{
    std::ios::sync_with_stdio( false );

    AoC::Input input;

    if( !input )
    {
        return 1;
    }

    this->Init( );

    while( input.Next( m_data ) )
    {
        this->Process( m_data );
    }

    this->Finish( );

    this->Teardown( );

    return 0;
}
