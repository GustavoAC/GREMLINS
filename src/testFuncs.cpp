/**
 * \file testFuncs.cpp
 * \brief Implementações dos métodos para a realização dos testes.
 * \author Gustavo Araújo Carvalho e Yuri Alessandro Martins
 */

#include "testFuncs.h"

unsigned int getRandomForSize() {
    std::random_device rd;
    return (rd() % 1901) + 100;
}

int getRandomTimeInterval() {
    std::random_device rd;
    return (rd() % 100) + 1;
}

void performanceTest(unsigned int numIterations){

    SLPool pool(2100);
    auto poolIsFaster = 0u;
    auto sysIsFaster = 0u;
    std::chrono::duration<double> longestPoolTime;
    std::chrono::duration<double> longestSysTime;
    std::chrono::duration<double> avPoolTime = std::chrono::steady_clock::duration::zero();
    std::chrono::duration<double> avSysTime = std::chrono::steady_clock::duration::zero();

    unsigned int randomSize1;
    unsigned int randomSize2;
    int *ptr1;
    int *ptr2;

    std::cout << "[[Fazendo um teste de performance com " << numIterations
              << " repetições]]\n";
    for (auto i = 1u; i <= numIterations; i++) {

        // Dividido por 2 * sizeof(int) pois são dois ponteiros de ints que podem
        // ocupar o espaço máximo.
        randomSize1 = getRandomForSize() / (2*sizeof(int));
        randomSize2 = getRandomForSize() / (2*sizeof(int));

        auto startPool = std::chrono::steady_clock::now();
        //================================================================================

        ptr1 = new (pool) int[randomSize1];
        ptr2 = new (pool) int[randomSize2];
        delete ptr1;
        delete ptr2;

        //================================================================================
        auto endPool = std::chrono::steady_clock::now();

        auto diffPool = endPool - startPool;

        auto startSys = std::chrono::steady_clock::now();
        //================================================================================

        ptr1 = new int[randomSize1];
        ptr2 = new int[randomSize2];
        delete ptr1;
        delete ptr2;

        //================================================================================
        auto endSys = std::chrono::steady_clock::now();

        auto diffSys = endSys - startSys;

        (diffPool < diffSys) ? poolIsFaster++ : sysIsFaster++;

        if (diffPool > longestPoolTime) longestPoolTime = diffPool;
        if (diffSys > longestSysTime) longestSysTime = diffSys;

        avPoolTime += ((endPool - startPool) - avPoolTime) / static_cast<double> (i);
        avSysTime += ((endSys - startSys) - avSysTime) / static_cast<double> (i);
    }

    std::cout << "Número de vezes que SLPool foi mais rápido: " << poolIsFaster << std::endl;
    std::cout << "Número de vezes que o sistema foi mais rápido: " << sysIsFaster << std::endl;
    std::cout << "Maior tempo do SLPool: "
        << std::chrono::duration <double, std::nano> (longestPoolTime).count() << " ns\n";
    std::cout << "Maior tempo do sistema: "
        << std::chrono::duration <double, std::nano> (longestSysTime).count() << " ns\n";
    std::cout << "Média dos tempos do SLPool: "
        << std::chrono::duration <double, std::nano> (avPoolTime).count() << " ns\n";
    std::cout << "Média dos tempos do sistema: "
        << std::chrono::duration <double, std::nano> (avSysTime).count() << " ns\n";
}

/*
class Event {
  public:

    Event() {}

    Event( void *_ptr, std::time_t _timestamp ) : mp_ptr( _ptr ),
                                                  mt_timestamp( _timestamp ) {}

    std::time_t getTimeStamp() const {
        return mt_timestamp;
    }

    void* getMemoryPtr() const {
        return mp_ptr;
    }

    bool operator<( const Event &_rhs ) const {
        return ( mt_timestamp < _rhs.mt_timestamp );
    }

  private:
    void *mp_ptr;
    std::time_t mt_timestamp;
};

void StoragePoolTest( StoragePool& _pool , std::time_t _timeLimit ) {
    std::priority_queue<Event> pq;

    // Run simulation for the time set by the client.
    for (std::time_t t( 0 ); t < _timeLimit; ++t) {
        while ( !pq.empty() ) { // Run while we have events pending or time to run.
            Event ev = pq.top(); // Access the event with the smallest time-stamp.
            if (ev.getTimeStamp() > t) break; // Still some time left....

            // When we got here, the top event has run out of time.
            pq.pop(); // Remove event from priority queue.
            _pool.Free( ev.getMemoryPtr() ); // Calling free operator.
        }

        auto memSize = getRandomForSize();
        void* const add = _pool.Allocate( memSize );
        auto elapsedTime = getRandomTimeInterval();
        std::time_t releaseTime = t + elapsedTime; // Set time stamp some time from now.
        pq.push( Event( add, releaseTime ) ); // Creating a new simulation event.
        // Here you might want to show the memory map on the screen ,
        // or write it to a log file, for debugging purpose.
    }
}
*/