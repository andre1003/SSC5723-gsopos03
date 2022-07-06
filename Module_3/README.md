# Módulo 3

Este módulo da disciplina de Sistemas Operacionais é um simulador de gerenciamento de memória virtual com paginação.

## 1. Informações Gerais

No simulador, os processos são submetidos e sua execução simulada por meio de uma série de referências a memórias. As referências são de leitura ou de gravação em um endereço virtual de memória. Assim, o simulador lê o arquivo ```config.txt```, que contêm informações sobre a "vida" do processo, contendo para cada processo, o tamanho de sua imagem e uma sequência de operações de acesso à memória principal, as quais podem ser as seguintes:

- Criar um processo **(C)**;
- Ler em memória **(R)**;
- Escrever em memória **(W)**;
- Executar instruções armazenadas na memória **(P)**;
- Executar instruções de E/S **(I)**.

As operações presentes no arquivo ```config.txt``` são inseridas antes da execução e cada linha do arquivo é composta com três itens:

1. **ID do processo:** identificador do processo;
2. **TAG da operação:** operação que é executada, a qual deve ser uma das definidas antes;
3. Esse item depende da TAG utilizada, podendo possuir as seguintes variações:
   - **Tamanho da imagem do processo** em kB, caso a TAG é utilizado;
   - Valor decimal de um **endereço lógico de memória** em binário na tabela de páginas do processo, se a TAG for R, W ou P;
   - Valor decimal do **identificador de um dispositivo de E/S** em binário, com a TAG I.

A seguir é apresentado um exemplo de uma configuração do arquvo de entrada. Nota-se que a notação (x)2 representa o valor x em binário.

```
P1 C 500
P1 R (0)2
P1 R (1024)2
P1 P (1)2
P1 R (2)2
P1 P (2)2
P1 W (1024)2
P7 C 1000
P7 R (4095)2
P7 R (800)2
P7 I (2)2
P7 R (801)2
P7 W (4096)2
P1 R (3)2
P1 R (4)2
P1 W (1025)2
P1 W (1026)2
```

Na sequência são explicadas algumas linhas (uma de cada operação) do exemplo anterior para melhor entendimento:

- **P1 C 500:** cria o processo com o identificador P1 com 500 kB de tamanho;
- **P1 R (0)2:** lê o conteúdo da memória no endereço lógico 0;
- **P1 P (1)2:** executa a instrução armazenada na memória no endereço lógico;
- **P1 W (1024)2:** escreve na memória no endereço lógico 1024.
- **P7 I (2)2**: executa instrução de E/S sobre o dispositivo 2.

**Observação:** As operações P e I são apenas simbólicas. Dessa forma, não é executada outra instrução na memória e há uma espera pela finalização de uma instrução de E/S, o que representa uma E/S programada.

Além disso, o simulador contém opções de configuração de mecanismos relacionados à memória virtual, como: tamanho das páginas e quadros de página; tamanho em bits do endereço lógico; tamanho da memória física; tamanho máximo da memória secundária; e tamanho da imagem de cada processo a ser executado. As opções de configuração são definidas manualmente nas constantes do arquivo ```config.h```, sendo possível alterá-las depois. A configuração atual é a seguinte:

```
// Virtual page size in kB
#define VIRTUAL_PAGE_SIZE 4
// Total virtual memory size
#define VIRTUAL_MEMORY_SIZE (VIRTUAL_PAGE_SIZE * 2000)
// Page frame size in kB
#define FRAME_SIZE VIRTUAL_PAGE_SIZE
// Total size of main memory
#define RAM_SIZE (FRAME_SIZE * 6)
// Secondary memory SWAP area size
#define SECONDARY_MEMORY_MAX_SIZE (FRAME_SIZE * 10000)
```

É importante destacar a multiplicidade dos valores na configuração, como exemplo, o tamanho da memória física (*RAM_SIZE*) é um múltiplo do tamanho da moldura (**FRAME_SIZE**), e assim por diante.

Por fim, para selecionar qual algoritmo de substituição de páginas é utilizado, basta definir **LRU** (algoritmo *Least Recently Used*) ou **CLOCK** (algoritmo do relógio) na constante ```CURRENT_METHOD```. Assim, o simulador seleciona o conjunto de funções adequado para executar.

-----


## 2. Políticas Adotadas

-----


## 3. Compilação e Execução

Para compilar o programa, execute o comando: ```make```.

**Observação:**  o comando ```make``` possibilita adicionar ```clean``` também para limpar o executável.

[Exemplos de execução]

-----
