/**
 * \file mempool_common.inl
 * \brief Sobrecarga de operadores para manipulação de memória (new e delete);
 */

 void * operator new ( size_t bytes, StoragePool * p ){
    Tag* const tag = reinterpret_cast <Tag *> ( p.Allocate(bytes + size_t(Tag)) );
    tag->pool = &p;
    // skip sizeof tag to get the raw data-block
    return ( reinterpret_cast <void *> ( tag + 1U ) );
 }
 
 void * operator new ( size_t bytes ){
    Tag* const tag = reinterpret_cast <Tag *>( std::malloc(bytes + sizeof(Tag)) );
    tag->pool = nullptr;
    // skip sizeof tag to get the raw data-block
    return ( reinterpret_cast <void *>( tag + 1U ) );
 }
 
 void operator delete ( void * arg ) noexcept{
    // We need to subtract 1U (in fact , pointer arithmetics ) because arg
    // points to the raw data ( second block of information ).
    // The pool id (tag) is located ‘sizeof (Tag)’ bytes before .
    Tag * const tag = reinterpret_cast<Tag *>( arg ) - 1U;
    if( nullptr != tag->pool )  //Memory block belongs to a particular GM.
        tag->pool->Free( tag );
    else
        std::free( tag );   // Memory block belongs to the operation system.
 }