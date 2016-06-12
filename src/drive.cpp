/**
 * \mainpage GREMLINS
 * \author Gustavo Araújo Carvalho
 * \author Yuri Alessandro Martins
 * \date Maio, 2016
 * \version 1.0
 * \file drive.cpp
 * \brief Arquivo principal de testes.
 */

#include <iostream>
#include <cassert>
#include "SLPool.h"
#include "mempool_common.h"
#include "testFuncs.h"

/**
 * \brief Função principal do programa que roda os testes da implementação.
 */
int main(){
    // Criando um Pool (GM).
    std::cout << "Criando o Pool com 200 bytes...\n";
    SLPool test_pool(400);
    test_pool.showStructure();

    // Primeiro teste de alocação.
    std::cout << "\nAlocando 1 inteiro...\n";
    int* t1 = new (test_pool) int;
    *t1 = 10;
    test_pool.showStructure();

    // Segundo teste de alocação.
    std::cout << "\nAlocando 4 arranjos de 10 inteiros...\n";

    int* ints[4];
    for(int i = 0; i < 4; i++){
        ints[i] = new (test_pool) int[10];
        test_pool.showStructure();
    }

    // Testando se os valores se mantém.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 10; j++){
            ints[i][j] = j;
            assert(ints[i][j] == j);
        }
    }

    // Primeiro teste de liberação. Tentando testar os 4 possíveis casos.
    std::cout << "\nLiberando ints[2]...\n";
    delete ints[2];
    std::cout << "O caso 2 do Free foi chamado: As áreas imediatamente antes" <<
    " e depois estão ocupadas.\n";
    test_pool.showStructure(true);

    std::cout << "\nLiberando ints[3]...\n";
    delete ints[3];
    std::cout << "O caso 1 do Free foi chamado: As áreas imediatamente antes" <<
    " e depois estão livres.\n";
    test_pool.showStructure();

    std::cout << "\nLiberando ints[1]...\n";
    delete ints[1];
    std::cout << "O caso 3 do Free foi chamado: A área anterior é reservada" <<
    " e a posterior é livre.\n";
    test_pool.showStructure();

    std::cout << "\nAlocando 1 inteiro (d1)...\n";
    int* d1 = new (test_pool) int;
    *d1 = 10;

    std::cout << "\nLiberando o inteiro [t1]...\n";
    delete t1;


    std::cout << "\nLiberando ints[0]...\n";
    delete ints[0];
    std::cout << "O caso 4 do Free foi chamado: A área anterior é livre e" <<
    " a posterior reservada.\n";
    test_pool.showStructure();

    // Testes para os métodos First-Fist e Best-Fist
    std::cout << "\n-------------------------------------------\n";
    std::cout << "Testes para os métodos First-Fist e Best-Fist\n";
    std::cout << "-------------------------------------------\n";
    std::cout << "\nAlocando 4 arranjos de 10 inteiros...\n";

    for(int i = 0; i < 4; i++){
        ints[i] = new (test_pool) int[10];
        test_pool.showStructure();
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 10; j++){
            ints[i][j] = j;
            assert(ints[i][j] == j);
        }
    }

    std::cout << "\nLiberando ints[0]...\n";
    delete ints[0];

    test_pool.showStructure(true);

#if BESTFIT
    std::cout << "\nRodando com o método BESTFIT:\n";
#else
    std::cout << "\nRodando sem o método BESTFIT:\n";
#endif

    std::cout << "\nRealocando ints[0]...\n";
    ints[0] = new (test_pool) int[10];

    test_pool.showStructure();

#if BESTFIT
    std::cout << "Na alocação, foi procurado espaço com o menor tamanho" <<
    " (ou igual tamanho, como nesse caso).\n";
    std::cout << "Isso siginifica que ele não foi alocado no primeiro espaço" <<
    " suficiente, mas sim no mais \"adequado\".\n\n";
#else
    std::cout << "O método Allocate buscou o primeiro espaço considerado" <<
    " \"suficiente\".\n\n";
#endif

    // Teste que compara a velocidade do SLPool e do sistema.
    performanceTest(100000);

    std::cout << "\n>>> Normal exiting..." << std::endl;
    return EXIT_SUCCESS;
}