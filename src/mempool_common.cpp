/**
 * \file mempool_common.cpp
 * \brief Sobrecarga de operadores para manipulação de memória (new e delete)
 * \author Gustavo Araújo Carvalho e Yuri Alessandro Martins
 */

#include "mempool_common.h"

void * operator new ( size_t bytes, StoragePool & p ){
#if BESTFIT
    Tag* const tag = reinterpret_cast <Tag *> ( p.AllocateBest(bytes + sizeof( Tag ) ) );
#else
    Tag* const tag = reinterpret_cast <Tag *> ( p.Allocate(bytes + sizeof( Tag ) ) );
#endif

    tag->pool = &p;
    // Skip sizeof tag to get the raw data-block
    return ( reinterpret_cast <void *> ( tag + 1U ) );
}

void * operator new[] ( size_t bytes, StoragePool & p ){
#if BESTFIT
    Tag* const tag = reinterpret_cast <Tag *> ( p.AllocateBest(bytes + sizeof( Tag ) ) );
#else
    Tag* const tag = reinterpret_cast <Tag *> ( p.Allocate(bytes + sizeof( Tag ) ) );
#endif

    tag->pool = &p;
    // Skip sizeof tag to get the raw data-block
    return ( reinterpret_cast <void *> ( tag + 1U ) );
}

void * operator new ( size_t bytes ){
    Tag* const tag = reinterpret_cast <Tag *>( std::malloc( bytes + sizeof( Tag ) ) );
    tag->pool = nullptr;
    // Skip sizeof tag to get the raw data-block
    return ( reinterpret_cast <void *> ( tag + 1U ) );
}

void operator delete ( void * arg ) noexcept{
    // We need to subtract 1U (in fact , pointer arithmetics ) because arg
    // points to the raw data ( second block of information ).
    // The pool id (tag) is located ‘sizeof (Tag)’ bytes before.
    Tag * const tag = reinterpret_cast<Tag *> ( arg ) - 1U;
    if( nullptr != tag->pool )  //Memory block belongs to a particular GM.
        tag->pool->Free( tag );
    else
        std::free( tag );   // Memory block belongs to the operation system.
}

void operator delete[] ( void * arg ) noexcept{
    // We need to subtract 1U (in fact , pointer arithmetics ) because arg
    // points to the raw data ( second block of information ).
    // The pool id (tag) is located ‘sizeof (Tag)’ bytes before.
    Tag * const tag = reinterpret_cast<Tag *> ( arg ) - 1U;
    if( nullptr != tag->pool )  //Memory block belongs to a particular GM.
        tag->pool->Free( tag );
    else
        std::free( tag );   // Memory block belongs to the operation system.
}