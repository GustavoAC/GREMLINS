# GREMLINS
GeREnciador de Memória com LIsta eNcadeada Simples.

Essa aplicação implementa um gerenciador de memória utilizando os conceitos de
lista encadeada vistos nas disciplinas de Estruturas de Dados Básica e Linguagem
de Programação, do curso de Bacharelado em Tecnologia da Informação da
Universidade Federal do Rio Grande do Norte (UFRN).

Um Gerenciador de Memórias (GM) requisita ao Sistema Operacional (SO) um bloco
de memória grande e se encarrega de distribuir blocos menores à aplicação
quando requisitado.

Para o método de alocação, foram utilizadas duas estratégias: First-Fit e Best-Fit.

A estratégia First-Fit basicamente procura o primero espaço grande suficiente
para a alocação, o que pode fazer com que a memória fique bastante fragmentada
(o que pode causar perda de desempenho e má utilização do espaço da memória).
Já o método Best-Fit, por outro lado, procura a melhor área para a alocação,
percorrendo a lista até achar a menor área suficiente para que a alocação
ocorra.

## Autores ##
- Gustavo Araújo Carvalho
- Yuri Alessandro Martins

## Como compilar ##
Para compilar essa aplicação, vá até o diretório principal e digite:

    $ make

Devido as duas políticas de alocação implementadas, o padrão estabelecido é o First-Fit.
Todavia, se quiser testar o programa com a implementação Best-Fit, basta digitar:

    $ make FIT=BESTFIT

Lembrando que para recompilar o programa é necessário antes limpar os arquivos
antigos, algo que pode ser feito facilmente com o comando

    $ make clean

## Para Executar ##
No diretório inicial do programa, digite no terminal:

    $ ./bin/exe