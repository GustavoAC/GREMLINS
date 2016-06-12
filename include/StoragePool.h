/**
 * \file StoragePool.h
 * \brief Implementação de uma classe que contém as operações fundamentais para
 * manipução de memória.
 * \author Gustavo Araújo Carvalho e Yuri Alessandro Martins
 */

#ifndef _STORAGE_POOL_H_
#define _STORAGE_POOL_H_

/**
 * \brief Classe que contém o conjunto de operações mais importantes para manipulação da memória
 */
class StoragePool{
public:

    /**
     * \brief Destructor da classe StoragePool.
     */
    virtual ~StoragePool() {}
    /**
     * \brief Requisita uma quantidade de memória.
     * \param bytes Quantidade de memória expressa em bits.
     * \return Ponteiro para a região de memória reservada.
     */
    virtual void* Allocate( size_t bytes ) = 0;
    /**
     * \brief Libera memória de uma região reservada.
     * \param ptr Ponteiro para a região reservada.
     */
    virtual void Free( void * ptr ) = 0;

     /**
     * \brief Requisita uma quantidade de memória, utilizando método Best-Fist.
     * \param bytes Quantidade de memória expressa em bits.
     * \return Ponteiro para a região de memória reservada.
     */
    virtual void * AllocateBest( size_t bytes ) = 0;

     /**
     * \brief Mostra a estrutura e a organização de um Pool.
     * \param showDetailed True para mostrar detalhes do Pool. False, caso contrário.
     */
    virtual void showStructure( bool showDetailed = false ) const = 0;
};

#endif