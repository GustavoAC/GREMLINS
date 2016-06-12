/**
 * \file testFuncs.h
 * \brief Implementação de funções de testes extras.
 * \author Gustavo Araújo Carvalho e Yuri Alessandro Martins
 */

#ifndef _TESTFUNCS_H_
#define _TESTFUNCS_H_

#include <ctime>
#include <chrono>
#include <queue>
#include <random>
#include "SLPool.h"
#include "mempool_common.h"

/**
 * \brief Gera um valor aleátorio.
 * \return Número aleátorio entre 100 e 2000.
 */
unsigned int getRandomForSize();

/**
 * \brief Gera um número aleátorio.
 * \return Número aleátorio entre 1 e 100.
 */
int getRandomTimeInterval();

/**
 * \brief Realiza um teste de performance do Pool com o SO.
 * \param numIterations Número de iterações.
 */
void performanceTest(unsigned int numIterations);

//void StoragePoolTest( StoragePool& _pool , std::time_t _timeLimit );


#endif
