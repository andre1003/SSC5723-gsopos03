# Módulo 1

Este módulo da disciplina de Sistemas Operacionais foi dividido em 2 itens:
•	Chamadas de Sistema
•	Processos CPU-Bound e I/O-Bound
Objetivo: identificar na prática alguns conceitos abordados em aula, como: chamadas de sistema, tipos de processos, trocas de contexto de processos, tempo de execução, entre outros.

## 1. Chamadas de Sistema

Foram selecionadas 3 primitivas de chamada de sistema disponíveis no Linux para cada categoria (gerenciamento de memória, processos, E/S e arquivos), devendo totalizar 9 para serem analisadas com a construção de programas.
As selecionadas foram:
- **Arquivos:** 
    - creat(); 
    - open(;
    - chmod();
- **Memória:** 
    - brk();
    - mmap();
    - munmap();
- **Processos:** 
    - execve();
    - fork();
    - kill();

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

**Todos os dados estatísticos dos respectivos programas foram coletados.**
**Eles estão dentro do diretório "analysis" deste diretório.**

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
Informações mínimas esperadas:
 - Tempo gasto em modo usuário
 - Tempo gasto em modo kernel
 - Tempo Total Decorrido
 - Porcentagem de uso da CPU (Tempo modo usuário + tempo modo kernel / tempo total decorrido) 
 - Trocas de contexto voluntárias
 - Trocas de contexto involuntárias

Para a obtenção desses dados foram aplicados aos programas CPU-bound e I/O-bound o respectivo comando abaixo.

**Todos os dados estatísticos dos programas de CPU-bound e I/O-bound acabaram sendo coletados.**
 **Eles estão armazenados dentro do diretório "analysis" deste diretório.**

```
/usr/bin/time ./main
```
Se quisessemos formatar a saída do __/usr/bin/time ./main__ poderíamos ter utilizado o parâmetro "-f".
Com este parâmetro, para trazer apenas as informações mínimas solicitadas por exemplo, o comando seria o seguinte:
```
/usr/bin/time -f " Tempo gasto em modo usuário (segundos): %U \n Tempo gasto em modo kernel (segundos): %S \n Tempo Total decorrido (segundos): %e \n Porcentagem de uso da CPU ( (%U + %S) / %e ): %P \n Trocas de contexto voluntárias: %w \n Trocas de contexto involuntárias: %c \n" ./main
```