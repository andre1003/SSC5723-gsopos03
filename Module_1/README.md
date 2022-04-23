# Módulo 1

Este módulo da disciplina de Sistemas Operacionais foi dividido em 2 itens:
- Chamadas de Sistema
- Processos CPU-Bound e I/O-Bound

**Objetivo**: 

Identificar na prática alguns conceitos abordados em aula, como: chamadas de sistema, tipos de processos, trocas de contexto de processos, tempo de execução, entre outros.


## 1. Informações Gerais

Foram selecionadas 3 primitivas de chamada de sistema disponíveis no Linux para cada categoria (gerenciamento de memória, processos, E/S e arquivos), devendo totalizar 9 para serem analisadas com a construção de programas.
Além disso, foram criados 2 programas para ilustrar o comportamento esperado para processos com características dos tipos CPU-bound e I/O-bound.

As primitivas de chamada de sistema selecionadas foram:
- **Arquivos:** 
    - _creat()_; 
    - _open()_;
    - _chmod()_;
- **Memória:** 
    - _brk()_;
    - _mmap()_;
    - _munmap()_;
- **Processos:** 
    - _execve()_;
    - _fork()_;
    - _kill()_;

E os programas CPU-bound e I/O-bound:
- **CPU-bound:** calcula valor de Pi através do método de Monte Carlo.
- **I/O-bound:** copia o conteúdo de um arquivo pra dentro de um novo arquivo.

--

### Compilação dos programas e execução

Para a execução dos programas é necessário o GCC que é o compilador originalmente escrito para Sistemas Operacionais GNU e que pode ser facilmente encontrado em distribuições Linux. 
Para compilar os programas e gerar os executáveis é necessário o seguinte comando para os respectivos programas:
```
gcc codigo.c -o nome_executavel
```
Uma vez gerado os executáveis, basta executar os programas com:
```
./nome_executavel
```

--


### Ferramenta strace

A ferramenta strace (http://man7.org/linux/man-pages/man1/strace.1.html) foi utilizada para obter as estatísticas relacionadas aos programas desenvolvidos, como as chamadas de sistema realizadas por eles e o tempo de processamento de cada uma.
Para obter as chamadas de sistema do "_execve()_" foi utilizado o seguinte comando:
```
strace ./nome_executavel
```
Para as estatísticas do "_execve()_" foi utilizado o mesmo comando, com a adição do parâmetro "_-c_":
```
strace -c ./nome_executavel
```

Já para a obtenção das chamadas de sistema e dos tempos de execução dos que utilizam "_fork()_" e "_kill()_" foram usados, respectivamente, os comandos abaixo.

Observe que o parâmetro “_-f_” é necessário para também catalogar a execução dos processos filhos que surgirem.

```
strace -f ./nome_executavel
```
```
strace -c -f ./nome_executavel
```

**Todos os dados estatísticos dos respectivos programas foram coletados.**

**Eles estão dentro do diretório "_analysis_".**

--


### Ferramenta time

A ferramenta "_time_" (https://linux.die.net/man/1/time) foi usada para obter estatísticas de uso de recursos em cada um dos programas desenvolvidos.

Para obter melhores resultados, foi utilizado o "_/usr/bin/time_" já contido no sistema Linux.

Informações mínimas esperadas:
 - Tempo gasto em modo usuário
 - Tempo gasto em modo kernel
 - Tempo Total Decorrido
 - Porcentagem de uso da CPU (Tempo modo usuário + tempo modo kernel / tempo total decorrido) 
 - Trocas de contexto voluntárias
 - Trocas de contexto involuntárias

A ferramenta "_time_" foi aplicada aos programas CPU-bound e I/O-bound através do comando:
```
/usr/bin/time ./nome_executavel
```
Se quisessemos formatar a saída do "_/usr/bin/time ./nome_executavel_" poderíamos ter utilizado o parâmetro "_-f_".

Com este parâmetro, para trazer apenas as informações mínimas solicitadas por exemplo, o comando seria o seguinte:
```
/usr/bin/time -f " Tempo gasto em modo usuário (segundos): %U \n Tempo gasto em modo kernel (segundos): %S \n Tempo Total decorrido (segundos): %e \n Porcentagem de uso da CPU ( (%U + %S) / %e ): %P \n Trocas de contexto voluntárias: %w \n Trocas de contexto involuntárias: %c \n" ./main
```

**Todos os dados estatísticos dos programas de CPU-bound e I/O-bound acabaram sendo coletados.**
 
 **Eles estão armazenados dentro do diretório "analysis".**
 
 
 -----
 

## 2. Chamadas de Sistema


Aqui vai conteudo das chamadas de sistema
    
    

-----


## 3. Tipos de Processos


Aqui vai conteudo dos tipos de processos
    
    
-----



