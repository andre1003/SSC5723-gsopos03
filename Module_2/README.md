# Módulo 2

Este módulo da disciplina de Sistemas Operacionais consiste na solução do problema do Produtor Consumidor.

## 1. Problema do Produtor Consumidor

O problema do Produtor e o Consumidor trata-se de um conjunto de processos que compartilham um mesmo buffer. Os processos chamados produtores colocam dados no buffer. Por sua vez, os processos denominados consumidores removem dados deste buffer.

[Descrever mais sobre isso]

-----


## 2. Compilação e Execução

Para compilar o programa, execute o comando: ```make```.

A execução é realizada com o comando ```./main```, sendo possível a inserção de parâmetros definidos. Os parâmetros são:

 - _-v, --verbose_: mais palavras do que o necessário na tela;
 - _-i, --interactions_: número de interações com o buffer;
 - _-s, --step-by-step_: passo a passo ao executar o programa (verbose é ativado);
 - _-h, --help_: exibir ajuda.

**Observação:** o comando ```make``` possibilita adicionar ```clean``` e ```help``` também para limpar o executável e exibir a ajuda, respectivamente.

-----


## 3. Visualização das Threads

Ao executar o programa, abra outro terminal e execute o comando ```htop```, sendo necessário aplicar ```./main```.

A partir disso, é possível a visualização da alternância dos processos produtores e consumidores.
