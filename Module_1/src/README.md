# Módulo 1

Este módulo da disciplina de Sistemas Operacionais foi dividido em 2 itens:
•	Chamadas de Sistema
•	Processos CPU-Bound e I/O-Bound
Objetivo: identificar na prática alguns conceitos abordados em aula, como: chamadas de sistema, tipos de processos, trocas de contexto de processos, tempo de execução, entre outros.

## 1. Chamadas de Sistema

Foram selecionadas 3 primitivas de chamada de sistema disponíveis no Linux para cada categoria (gerenciamento de memória, processos, E/S e arquivos), devendo totalizar 9 para serem analisadas com a construção de programas.
As selecionadas foram:
 - Arquivos: creat(), open() e chmod()
 - Memória: brk(), mmap() e munmap()
 - Processos: execve(), fork() e kill()

### Execução dos programas

Para a execução dos programas é necessário o GCC que é o compilador originalmente escrito para Sistemas Operacionais GNU e que pode ser facilmente encontrado em distribuições Linux. 
Para compilar os programas e gerar os executáveis foi necessário o seguinte comando para os respectivos programas:
```
gcc codigo.c -o nome_executavel
```

### Ferramenta strace

A ferramenta strace (http://man7.org/linux/man-pages/man1/strace.1.html) foi utilizada para obter as estatísticas relacionadas aos programas desenvolvidos, como as chamadas de sistema realizadas por eles e o tempo de processamento de cada uma.
Para obter as chamadas de sistema e tempos de execução do que utiliza o execve() foram usados, respectivamente:
```
strace ./main
```
```
strace -c ./main
```

E para obtenção das chamadas de sistema e dos tempos de execução dos que utilizam fork() e kill() foram usados, respectivamente, os comandos abaixo.
Observe que o “-f” é usado para também catalogar a execução dos processos filhos que surgirem.
```
strace -f ./main
```
```
strace -c -f ./main
```




## 2. Tipos de Processos

Foram criados 2 programas para ilustrar o comportamento esperado para processos CPU-bound e I/O-bound.

### Ferramenta time

A ferramenta time (https://linux.die.net/man/1/time) foi usada para obter estatísticas de uso de recursos em cada um dos programas desenvolvidos.












