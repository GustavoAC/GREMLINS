/**
 * \file StoragePool.h
 * \brief Implementação de uma classe que contém as operações fundamentais para
 * manipução de memória.
 */
 
class StoragePool{
public:
    virtual ~StoragePool();
    /**
     * \brief Requisita uma quantidade de memória.
     * \param size_t Quantidade de memória expressa em bits.
     * \return Ponteiro para a região de memória reservada.
     */
    virtual void* Allocate( size_t ) = 0;
    /**
     * \brief Libera memória de uma região reservada.
     * \param Ponteiro para a região reservada.
     */
    virtual void Free( void * ) = 0;
 }