/**
 * \file mempool_common.h
 * \brief 
 */

#include <stdio.h>
#include "StoragePool.h"

struct Tag{
    StoragePool * pool;
};

/**
 * \brief Aloca memória para um GM
 * \param bytes Tamanho do bloco de memória que será alocado.
 * \param p Ponteiro para o GM usado.
 */
void * operator new ( size_t bytes, StoragePool * p );
/**
 * \brief Aloca memória.
 * \param Tamanho do bloco de memória que será alocado.
 */
void * operator new ( size_t bytes );
/**
 * \brief Deleta memória associada a um GM.
 * \param arg Ponteiro para o ínicio do bloco de memória que deve ser liberado.
 */
void operator delete ( void * arg ) noexcept;