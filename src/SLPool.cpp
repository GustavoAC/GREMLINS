/**
 * \file SLPool.cpp
 * \brief Implementações dos métodos da classe SLPool.
 * \author Gustavo Araújo Carvalho e Yuri Alessandro Martins
 */

#include "SLPool.h"

SLPool::SLPool( size_t bytes ) :
    mui_NumberOfBlocks( std::ceil( ( bytes+sizeof( SLPool::Header) )
                    / static_cast<float> ( sizeof( SLPool::Block ) ) ) ),
    mp_Pool( new Block[ mui_NumberOfBlocks + 1 ] ), // +1 para o Sentinel.
    mr_Sentinel ( mp_Pool[ mui_NumberOfBlocks ] )
    {
        mp_Pool[0].mui_length = mui_NumberOfBlocks;
        mp_Pool[0].mp_Next = nullptr;
        mr_Sentinel.mp_Next = &mp_Pool[0];

    }

SLPool::~SLPool(){
    delete [] mp_Pool;
}

void * SLPool::Allocate( size_t bytes ){
    // Descobre o número de blocos necessários.
    unsigned int neededBlocks = std::ceil( ( bytes + sizeof( SLPool::Header) ) /
        static_cast<float> ( sizeof( SLPool::Block ) ) );



    // Procura por espaço pra pôr eles (usado para o método First fit)
    Block * before = &mr_Sentinel;
    Block * work = mr_Sentinel.mp_Next;

    // Percorre todo em pool em busca de área livre.
    while ( work != nullptr and work->mui_length < neededBlocks ){
        before = work;
        work = work->mp_Next;
    }

    // Se não encontrar espaço, retorna bad_alloc (indicando ao cliente falta de espaço).
    if ( work == nullptr ) throw std::bad_alloc();

    // work->mp_Next = Próximo block livre apontado

    // Se encontrou o espaço, aloca.
    if ( neededBlocks == work->mui_length ){
        before->mp_Next = work->mp_Next;
    }else{
        Block * newBlockStartpoint = work + neededBlocks; // New free block
        newBlockStartpoint->mp_Next = work->mp_Next;
        before->mp_Next = newBlockStartpoint;

        newBlockStartpoint->mui_length = work->mui_length - neededBlocks;
        work->mui_length = neededBlocks;
    }

    // Retorna um ponteiro para a área reservada.
    Header * const aux = reinterpret_cast <Header *> ( work );
    return ( reinterpret_cast <void *> ( aux + 1U ) );
}

void * SLPool::AllocateBest( size_t bytes ){
    // Descobre o número de blocos necessários.
    unsigned int neededBlocks = std::ceil( ( bytes + sizeof( SLPool::Header) ) /
        static_cast<float> ( sizeof( SLPool::Block ) ) );


    // Procura por espaço pra pôr eles (First fit)
    Block * before = &mr_Sentinel;
    Block * work = mr_Sentinel.mp_Next;
    Block * beforeBest = before;
    Block * best = work;

    while ( work != nullptr ){
        // Implementação do Best-fit. Busca pelo espaço "mais adequado".
        if ( work->mui_length >= neededBlocks and
           ( work->mui_length < best->mui_length or best->mui_length < neededBlocks ) ) {
            beforeBest = before;
            best = work;
        }
        // Se o tamanho for exatamente o procurado, acaba o laço.
        if ( best->mui_length == neededBlocks ) break;

        before = work;
        work = work->mp_Next;
    }

    // Se não achar uma área, acontece bad_alloc (informa ao cliente que não houve alocação).
    if ( best->mui_length < neededBlocks ){
        std::cout << "BAD ALLOC A SEGUIR";
        std::cout << best->mui_length << "\n";
        std::cout << neededBlocks << "\n";

        throw std::bad_alloc();

    }

    // work->mp_Next = Próximo block livre apontado

    // Ao encontrar a melhor área, faz os procedimentos para alocação.
    if ( neededBlocks == best->mui_length ){
        beforeBest->mp_Next = best->mp_Next;
    }else{
        Block * newBlockStartpoint = best + neededBlocks; // New free block

        newBlockStartpoint->mp_Next = best->mp_Next;
        newBlockStartpoint->mui_length = best->mui_length - neededBlocks;

        beforeBest->mp_Next = newBlockStartpoint;
        best->mui_length = neededBlocks;
    }

    // Retorna um ponteiro para a área reservada.
    Header * const aux = reinterpret_cast <Header *> ( best );
    return ( reinterpret_cast <void *> ( aux + 1U ) );
}


void SLPool::Free( void * inputPtr ){
    // Reiterpretar o ponteiro para void como um ponteiro para Header.
    Header *aux = reinterpret_cast<Header *> ( inputPtr );
    Block * ptr = reinterpret_cast<Block *> ( aux - 1U );

    // Caso especial: o GM está completamente lotado.
    if ( mr_Sentinel.mp_Next == nullptr ) {
        mr_Sentinel.mp_Next = ptr;
        ptr->mp_Next = nullptr;
        return;
    }

    // Declara dois blocos auxiliares.
    Block * before = &mr_Sentinel;          // Bloco que será o "antes" do que queremos liberar.
    Block * after = mr_Sentinel.mp_Next;    // Bloco que será o "depois" do que queremos liberar.

    // Tenta encontrar duas áreas livres entre o ptr (que não a primeira).
    while ( after->mp_Next != nullptr and after <= ptr ){
        before = before->mp_Next;   // Incrementa o ponteiro do bloco "anterior".
        after = after->mp_Next;     // Incrementa o ponteiro do bloco que será o "posterior".
    }

    // Quando os blocos "posteriores" e "anteriores" são encontrados, existem quatro casos de liberação:

    // Caso 1. As áreas imediatamente anterior e posterior são livres.
    if( ( ptr + ptr->mui_length == after ) and ( ptr - before->mui_length == before ) ){
        before->mui_length += (ptr->mui_length + after->mui_length);
        before->mp_Next = after->mp_Next;


    }

    // 3. A área imediatamente anterior é reservada e a posterior é livre
    else if( ptr + ptr->mui_length == after ){
        ptr->mui_length += after->mui_length;
        before->mp_Next = ptr;
        ptr->mp_Next = after->mp_Next;


    }

    // 4. A área imediatamente anterior é livre e a posterior é reservada.
    else if( ptr - before->mui_length == before ) {
        before->mui_length += ptr->mui_length;


    }

    // 2. As áreas imediatamente anterior e posterior são reservadas.
    else{;
        before->mp_Next = ptr;
        ptr->mp_Next = after;
    }
}

void SLPool::showStructure( bool showDetailed ) const {

    // Ponteiro pra lista de blocos livres.
    Block * listPointer = mr_Sentinel.mp_Next;

    // Ponteiro que percorre por tudo.
    Block * work = mp_Pool;

    auto occBlocks = 0u;            // Blocos ocupados.
    auto freeBlocks = 0u;           // Blocos livres;
    auto numOccAreas = 0u;          // Número de áres ocupadas.
    auto numFreeAreas = 0u;         // Número de áres livres.
    auto largestOccArea = 0u;       // Maior área ocupada.
    auto largestFreeArea = 0u;      // Maior área livre.

    char toPrint;

    // Percorre todo o pool.
    while ( work != &mr_Sentinel ) {

        // Enquanto listPointer tá antes de work
        while ( listPointer < work and listPointer != nullptr ) {
            listPointer = listPointer->mp_Next;

        }




        // Se work e listPointer iguais, work está numa área vazia.
        // Se não, work está numa área ocupada.
        if ( work == listPointer ) {
            toPrint = '-';
            numFreeAreas++;
            freeBlocks += work->mui_length;
            if ( work->mui_length > largestFreeArea )
                largestFreeArea = work->mui_length;
        } else {
            toPrint = '*';
            numOccAreas++;
            occBlocks += work->mui_length;
            if ( work->mui_length > largestOccArea )
                largestOccArea = work->mui_length;
        }

        // Coloca no terminal a área (ocupada ou livre).
        std::cout << "[";
        for ( auto i = 0u; i < work->mui_length; i++ )
            std::cout << toPrint;
        std::cout << "]";

        // Incremento do ponteiro auxiliar.
        work += work->mui_length;
    }

    std::cout << std::endl;

    // Se a opção de mostrar detalhes estiver ativa, coloca as informações extras na tela:
    if ( showDetailed ){
        std::cout << "[Stats]:\n";
        std::cout << "Number of free blocks: " << freeBlocks;
        std::cout << " (Free bytes: " << freeBlocks * sizeof(SLPool::Block) << ").\n";
        std::cout << "Number of occupied blocks: " << occBlocks;
        std::cout << " (Used bytes: " << occBlocks * sizeof(SLPool::Block) << ").\n";
        std::cout << "Number of free areas: " << numFreeAreas << ".\n";
        std::cout << "Number of occupied areas: " << numOccAreas << ".\n";
        std::cout << "Largest free area (in blocks): " << largestFreeArea << ".\n";
        std::cout << "Largest occupied area (in blocks): " << largestOccArea << ".\n";
    }
}