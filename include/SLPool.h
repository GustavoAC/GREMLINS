/**
 * \file SLPool.h
 * \brief 
 */

class SLPool : public StoragePool{
public:
    struct Header{
        unsigned int mui_lenght;
        Header() : mui_lenght(0u) { /* Empty */ };
    };
    
    struct Block : public Header{
        enum { BlockSize = 16 };    //Eache block has 16 bytes
        union{
            Block *mp_Next;
            char mc_RawArea[ BlockSize - sizeof( Header ) ];
        };
        Block() : Header(), mp_Next( nullptr ) { /* Empty */ };
    };
    
private:
    unsigned int mui_NumberOfBlocks;
    Block *mp_Pool; //!< Head of list.
    Block &mr_Sentinel; //!< End of the list.
    
public:
    explicit SLPool( size_t );
    ~SLPool();
    void * Allocate( size_t );
    void Free( void * )
}