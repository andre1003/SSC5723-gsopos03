# Módulo 2

Este módulo da disciplina de Sistemas Operacionais consiste na solução do problema do Produtor Consumidor aplicando semáforos.

## 1. Problema do Produtor Consumidor

O problema do Produtor e o Consumidor trata-se de um conjunto de processos que compartilham um mesmo _buffer_. Os processos chamados produtores colocam dados no _buffer_. Por sua vez, os processos denominados consumidores removem dados deste _buffer_. Assim, o produtor insere na região que ainda não houve consumo e o consumidor remove dessa região. Este problema é clássico em sistemas operacionais, o qual procura exemplificar as situações de impasses no gerenciamento de processos, além de preocupar com acessos indevidos em recursos compartilhados e no sincronismo entre processos. Para solucionar o problema é necessário que:

- Se o _buffer_ estiver cheio, o processo produtor é bloqueado;
- Se o _buffer_ estiver vazio, o processo consumidor é bloqueado;
- Apenas um processo pode acessar o _buffer_ em um determinado instante.

Como solução ao problema, ou seja, o controle do acesso as variáveis compartilhadas e garantia de sincronismo nas operações, os semáforos são utilizados. O semáforo consiste em uma variável (ou tipo abstrato de dados) especial, que é protegida e possui a função de controlar o acesso aos recursos compartilhados em um ambiente multitarefa. Outro controle relevante é a espera ociosa, pois quando um processo não está liberado para ler ou gravar, deve entrar em um estado de espera para não consumir o processamento, e depois, ser avisado quando pode voltar no processamento. Dessa forma, a solução utiliza três semáforos:

- **_Full_:** iniciado com 0, conta o número de _slots_ no _buffer_ que estão ocupados;
- **_Empty_:** iniciado com o número total de _slots_ no _buffer_, conta o número de _slots_ no _buffer_ que estão vazios;
- **_Mutex_ (ou semáforo binário):** iniciado com 1, garante que os processos produtor e consumidor não acessem o _buffer_ simultaneamente.

Os semáforos _full_ e _empty_ resolvem o problema da sincronização, e o _mutex_ possibilita a exclusão mútua, isto é, a garantia que um processo não terá acesso à região crítica quando outro processo está utilizando essa região.

Portanto, para solucionar este problema, as seguintes condições foram requisitadas ao programa:

- O programa deve ter um _buffer_ limitado, acessível a qualquer processo decorrente do processo principal;
- O programa deve ter uma fila apontando para o próximo endereço livre, a ser escrito;
- O programa deve ter uma fila apontando para o próximo endereço ocupado, a ser lido e liberado;
- O programa deve controlar as seções críticas, para que não haja acessos indevidos;
- O programa deve ter a capacidade de colocar um processo em modo de espera;
- O programa deve ter a capacidade de controlar quando um processo está em espera, para poder "chamar" o mesmo;
- O programa deve controlar quantos endereços estão livres e quantos endereços estão ocupados.

Finalmente, a biblioteca _pthreads_ (http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html) é utilizada para a programação de forma concorrente com as funcionalidades de criação, controle e suspensão de _threads_, além da execução e controle de exclusão mútua por semáforos binários. Além disso, a biblioteca _semaphore_ para a implementação dos semáforos _full_ e _empty_, o qual adiciona algumas funcionalidades extras de semáforo sobre a biblioteca anterior.

-----


## 2. Compilação e Execução

Para compilar o programa, execute o comando: ```make```.

A execução é realizada com o comando ```./main```, sendo possível a inserção de parâmetros definidos. Os parâmetros são:

 - _-v, --verbose_: mais palavras do que o necessário na tela;
 - _-i, --interactions_: número de interações com o _buffer_, o que permite o programa finalizar a execução após um número _x_ de interações;
 - _-s, --step-by-step_: passo a passo ao executar o programa, sendo o _verbose_ ativado automaticamente;
 - _-h, --help_: exibir ajuda de como executar e os parâmetros (opções).

**Observação 1:** o comando ```make``` possibilita adicionar ```clean``` e ```help``` também para limpar o executável e exibir a ajuda, respectivamente.

**Observação 2:** é possível alterar o tamanho máximo do _buffer_ e o número máximo de _threads_. Para isso, é necessário alterar as constantes que estão no início do arquivo _main.c_:
```
#pragma region Defines
/* DEFINES */
#define MAX_BUFFER_SIZE     5       // Maximum number of elements in buffer node list
#define TRUE                1       // True const value
#define FALSE               0       // False const value
#define MAX_THREADS         10      // Maximum number of threads
#define MAX_INTERACTIONS    100000  // Maximum number of interactions with the buffer
#pragma endregion
```

**Observação 3:** em cada execução, um arquivo _logs.txt_ é gerado na pasta, o que permite notar a sequência do processo produtor e consumidor.

-----


## 3. Visualização das _Threads_

Ao executar o programa, abra outro terminal e execute o comando ```htop```, sendo necessário aplicar o filtro ```./main```.

A partir disso, é possível a visualização da alternância dos processos produtores e consumidores.
