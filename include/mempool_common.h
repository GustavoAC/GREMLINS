/**
 * \file mempool_common.h
 * \brief Métodos comuns a todas as classes.
 * \author Gustavo Araújo Carvalho e Yuri Alessandro Martins
 */

#include <iostream>
#include "StoragePool.h"

#ifndef _MEMPOOL_COMMON_H_
#define _MEMPOOL_COMMON_H_

/**
 * \brief Contém um ponteiro para o Pool ao qual um bloco pertence.
 */
struct Tag{
    StoragePool * pool;					//!< Ponteiro para o pool.
};

/**
 * \brief Aloca memória para um GM
 * \param bytes Tamanho do bloco de memória que será alocado.
 * \param p Ponteiro para o GM usado.
 */
void * operator new ( size_t bytes, StoragePool & p );

/**
 * \brief Aloca memória para um GM. Sobrecarga para arranjos.
 * \param bytes Tamanho do bloco de memória que será alocado.
 * \param p Ponteiro para o GM usado.
 */
void * operator new[] ( size_t bytes, StoragePool & p );

/**
 * \brief Aloca memória.
 * \param bytes Tamanho do bloco de memória que será alocado.
 */
void * operator new ( size_t bytes );

/**
 * \brief Deleta memória associada a um GM.
 * \param arg Ponteiro para o ínicio do bloco de memória que deve ser liberado.
 */
void operator delete ( void * arg ) noexcept;

/**
 * \brief Deleta memória associada a um GM. Sobrecarga para arranjos.
 * \param arg Ponteiro para o ínicio do bloco de memória que deve ser liberado.
 */
void operator delete[] ( void * arg ) noexcept;

#endif