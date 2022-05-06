# Módulo 1

Este módulo da disciplina de Sistemas Operacionais foi dividido em duas partes:
- Chamadas de sistema (do inglês *syscalls* ou *system calls*);
- Processos CPU-*bound* e I/O-*bound*.

## 1. Informações Gerais

Foram selecionadas três primitivas de chamada de sistema disponíveis no Linux para cada categoria (gerenciamento de memória, processos, E/S e arquivos), totalizando nove para serem analisadas com a construção de programas, que exemplificam a utilização de cada uma das primitivas.
Ainda, foram criados dois programas para ilustrar o comportamento esperado para processos com características dos tipos CPU-*bound* e I/O-*bound*. A respeito dos programas de CPU-*bound* e I/O-*bound*:

- **CPU-_bound_:** calcula uma aproximação do valor de π (pi) por meio do método de Monte Carlo.
- **I/O-_bound_:** copia o conteúdo de um arquivo anterior (existente) pra dentro de um novo arquivo, e assim por diante.


### Compilação dos programas e execução

Para a execução dos programas é necessário o GNU *Compiler* C (GCC) que é o compilador originalmente escrito para Sistemas Operacionais GNU e que pode ser facilmente encontrado em distribuições Linux. 
Para compilar os programas e gerar os executáveis é necessário o seguinte comando para os respectivos programas:
```
gcc code.c -o executable_name
```
Uma vez gerado os executáveis, basta executar os programas com:
```
./executable_name
```

**Observação:** no programa de CPU-*bound* é preciso inserir o parâmetro "_-lm_" ao compilar, pois utiliza a biblioteca **math.h** para os cálculos.


### Ferramenta strace

A ferramenta strace (http://man7.org/linux/man-pages/man1/strace.1.html) foi utilizada para obter as estatísticas relacionadas aos programas desenvolvidos, como as chamadas de sistema realizadas e o tempo de processamento de cada uma. Para obter as chamadas de sistema em geral, foi utilizado o seguinte comando:
```
strace ./executable_name
```
Para as estatísticas foi utilizado o mesmo comando, com a adição do parâmetro "_-c_":

```
strace -c ./executable_name
```

Especificamente, a obtenção das *syscalls* e dos tempos de execução dos que utilizam "_fork()_" e "_kill()_" foram usados, respectivamente:

```
strace -f ./executable_name
```
```
strace -c -f ./executable_name
```

**Observação:** o parâmetro "_-f_" é necessário para também catalogar a execução dos processos filhos que surgirem.


### Ferramenta time

A ferramenta "_time_" (https://linux.die.net/man/1/time) foi utilizada para obter estatísticas de uso de recursos nos programas de CPU-*bound* e I/O-*bound*.
Para obter melhores resultados, foi utilizado o "_/usr/bin/time_", o qual está contido no sistema Linux. As informações mínimas esperadas nesta etapa são:

 - Tempo gasto em modo usuário;
 - Tempo gasto em modo kernel;
 - Tempo total decorrido;
 - Porcentagem de uso da CPU ```[(tempo modo usuário + tempo modo kernel) / tempo total decorrido]```; 
 - Trocas de contexto voluntárias;
 - Trocas de contexto involuntárias.

A ferramenta "_time_" foi aplicada aos programas CPU-*bound* e I/O-*bound* por meio do comando:
```
/usr/bin/time -v ./executable_name
```
Contudo, se quiser formatar a saída do "_/usr/bin/time ./executable_name_" pode utilizar o parâmetro "_-f_".
Com esse parâmetro, para trazer somente as informações mínimas apresentadas, o comando é:
```
/usr/bin/time -f "\n\n>> Minimum information:\n\n  Time spent in user mode (seconds): %U \n  Time spent in kernel mode (seconds): %S \n  Total elapsed time (seconds): %e \n  CPU usage percentage ((%U + %S) / %e): %P \n  Voluntary context switches: %w \n  Involuntary context switches: %c \n" ./main
```

-----


## 2. Chamadas de Sistema

Uma *syscall* é o mecanismo programático pelo qual um programa de computador solicita um serviço ao núcleo sobre o qual está sendo executado. Como comentado anteriormente, três primitivas de chamada de sistema Linux foram selecionadas, sendo:

- E/S e arquivos: 
    - ```creat()```: cria um novo arquivo ou reescreve um já existente; 
    - ```open()```: abre um arquivo em um determinado caminho _path_. Caso o arquivo não exista, o arquivo é criado;
    - ```chmod()```: altera a permissão do arquivo especificado.
- Gerenciamento de memória:
    - ```brk()```: define o final do segmento de dados em um determinado endereço _addr_;
    - ```mmap()```: cria um novo mapeamento no espaço de endereço virtual do processo chamado;
    - ```munmap()```: exclui os mapeamentos para um trecho de memória especificado.
- Processos:
    - ```execve()```: executa um programa especificado em um caminho _path_;
    - ```fork()```: cria um novo processo filho duplicando o processo pai;
    - ```kill()```: envia um sinal qualquer para um processo ou um grupo de processos.

Após a implementação, todos os dados estatísticos das chamadas de sistema foram coletados, sendo armazenados no diretório ```analysis```.

Além das chamadas de sistemas selecionadas listadas acima, outras chamadas também apareceram nas estatísticas dos programas exemplos da primeira parte, como read, write, close, fstat, mprotect, rt_sigaction, rt_sigprocmask, pread64, access, clone, wait4,arch_prctl, openat, arch_prctl, lseek, clock_nanosleep, getpid, clone, getppid e clock_nanosleep.

-----


## 3. Tipos de Processos

Os processos CPU-*bound* são aqueles que utilizam a CPU na maior parte de seu tempo de execução. Assim, esses processos são mais rápidos se o desempenho da CPU for bom. Em contrapartida, os processos I/O-*bound* são os que dependem mais das entradas e saídas do sistema. Dessa forma, quando um certo dispostivo possui um desempenho excelente, como exemplo, o uso de SSD ao invés de disco rígido, os processos I/O-*bound* são mais eficientes.  

**Observação:** todos os dados estatísticos dos programas de CPU-*bound* e I/O-*bound* foram coletados, os quais foram salvos na pasta ```analysis```.

### 3.1. CPU-*bound*

No programa de CPU-*bound* é realizado o cálculo de uma aproximação ao valor de π (pi) por meio do método de Monte Carlo, que faz o uso de números aleatórios. O que se faz é sortear um grande número de pontos em um plano cartesiano, no qual se define um quadrado de lado _2.R_ e uma circunferência inscrita no quadrado, de raio _R_. Sorteia-se então uma certa quantidade _N_ de coordenadas dentro do plano cartesiano, contando-se quantas dessas coordenadas estão dentro da circunferência (_k_). Considerando uma distribuição homogênea de coordenadas é possível admitir que essas quantias são equivalentes:

- Área do quadrado ```A = 4.R²```;
- Área do círculo ```B = π.R²```.

Se B e A forem respectivamente o total de coordenadas dentro da circunferência e o total de coordenadas sorteadas, tem que o valor de π é dado pela equação: ```π = 4.(B/A)```.

A partir disso, os seguintes dados foram retornados na ferramenta "_time_":

 - Tempo gasto em modo usuário: 1.59 segundos;
 - Tempo gasto em modo kernel: 0.00 segundos;
 - Tempo total decorrido: 1.60 segundos;
 - Porcentagem de uso da CPU: 99%; 
 - Trocas de contexto voluntárias: 17;
 - Trocas de contexto involuntárias: 0.

É possível observar que a CPU atingiu quase 100% de uso ao executar o processo do tipo CPU-*bound*.

### 3.2. I/O-*bound*

No programa de I/O-*bound* é realizada uma cópia de um arquivo anterior (existente) para dentro um novo arquivo (atual), e processo se repete até atingir um número _x_ de arquivos gerados. Ao final da operação, todos os arquivos são removidos, com exceção do primeiro.

Baseado nisso, as seguintes informações foram obtidas na ferramenta "_time_":

 - Tempo gasto em modo usuário: 0.01 segundos;
 - Tempo gasto em modo kernel: 0.00 segundos;
 - Tempo total decorrido: 0.03 segundos;
 - Porcentagem de uso da CPU: 26%; 
 - Trocas de contexto voluntárias: 224;
 - Trocas de contexto involuntárias: 0.

Nota-se que a CPU teve apenas 26% de uso quando o processo é do tipo I/O-*bound*. Além disso, o número elevado de trocas de contexto voluntárias, o qual acontece por conta da quantidade de arquivos que são gerados e depois excluídos.
