/**
 * \file SLPool.h
 * \brief Implementação da classe SLPool.
 * \author Gustavo Araújo Carvalho e Yuri Alessandro Martins
 */

#ifndef _SLPOOL_H_
#define _SLPOOL_H_

#include <iostream>
#include <cmath>
#include <new>
#include "StoragePool.h"


/**
 * \brief Classe que implementa uma memória com lista encadeada simples.
 */
class SLPool : public StoragePool{
public:
    /**
     * \brief Header contém as informações sobre um bloco (tamanho).
     */
    struct Header{
        unsigned int mui_length;                    //!< Tamanho do bloco.
        Header() : mui_length(0u) { /* Empty */ };  //!< Construtor do registro.
    };

    /**
     * \brief Implementação de um bloco, uma unidade básica utilizada pelo cliente.
     */
    struct Block : public Header{
        enum { BlockSize = 16 };    //<! Each block has 16 bytes
        union{
            Block *mp_Next;         //<! Ponteiro para o próximo bloco livre.
            char mc_RawArea[ BlockSize - sizeof( Header ) ]; //!< Área de armazenamento.
        };
        Block() : Header(), mp_Next( nullptr ) { /* Empty */ }; //!< Construtor do bloco.
    };

    /**
     * \brief Constructor da classe SLPool.
     * \param bytes Tamanho do Pool expresso em bytes.
     */
    explicit SLPool( size_t bytes );

    /**
     * \brief Destructor da classe SLPool.
     */
    ~SLPool();

    /**
     * \brief Requisita uma quantidade de memória expressa em bytes.
     * Implementação com modo First-Fit.
     * \param bytes Quantidade de memória a ser reservada.
     * \return Ponteiro para a região rerservada.
     */
    void * Allocate( size_t bytes );

    /**
     * \brief Requisita uma quantidade de memória expressa em bytes.
     * Implementação com modo Best-Fit.
     * \param bytes Quantidade de memória a ser reservada.
     * \return Ponteiro para a região rerservada.
     */
    void * AllocateBest( size_t bytes );

    /**
     * \brief Libera uma região reservada pela função Allocate.
     * \param inputPtr Ponteiro para a região rerservada que deve ser liberada.
     */
    void Free( void * inputPtr );

    /**
     * \brief Exibe a estrutura atual do pool, indicando o tamanho dos blocos
     * e o seu conteúdo de forma visual e textual no console.
     * \param showDetailed Indica a exibição ou não da informação textual
     * detalhada (o valor padrão é falso).
    */
    void showStructure( bool showDetailed = false ) const;

private:
    unsigned int mui_NumberOfBlocks; //!< Number of blocks.
    Block *mp_Pool; //!< Head of list.
    Block &mr_Sentinel; //!< End of the list.

};

#endif