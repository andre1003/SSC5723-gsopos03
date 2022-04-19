#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // Declaração de variável que receberá o ID de retorno do fork() na criação do novo processo
    pid_t id;

    /* 
        Declaração de variaveis utilizadas. Altere os valores se quiser.
        O "sec" é para estabelecer um sleep e acompanhar no console as execuções.
        O "num" é para ilustrar que o novo processo é uma cópia do pai (tanto que compartilham mesmo endereço de endereçamento), 
        mas, apesar disso, a alteração do valor pelo filho não afeta o valor do pai.
    */
    int sec = 3;
    int num = 10;
    
    printf("------------------- \n");
    printf(" Iniciando execução \n");
    printf("------------------- \n");
    sleep(sec);

    // Criar um novo processo (fork) e recebe como retorno o pid_t da chamada de sistema
    id = fork();

    // Se o ID retornado da chamada for MAIOR que zero (0), então estamos no processo PAI
    if (id > 0){
        /*
            O código aqui é executado pelo processo PAI.
            É exibido em tela algumas informações que identifique isso, como: 
            PID do PAI, espaço de endereçamento usado por "num" e o valor lá contido.
        */
        printf(" [PAI]: Meu PID é -> %i \n", getpid());
        printf(" [PAI]: Tenho o numero %i que está no endereço '%p' \n", num, &num);
        printf(" [PAI]: Agora vou esperar a execução de meu filho \n");
        
        /*
            O wait() também é uma primitiva de chamada de sistema! 
            Apesar do foco ser ilustrar o fork(), 
            ele foi usado aqui para bloquear o processo pai até que o filho se encerre
        */
        wait(NULL);

        /*
            Após o término do processo filho, o pai pode encerrar.
            Mas antes de encerrar, é exibido em tela o valor que o pai contém no espaço de endereçamento.
            É observado que o valor não sofre mudança apesar da execução e manipulação do valor pelo filho.
        */
        printf(" [PAI]: Meu numero ainda é -> %i \n", num);
        printf(" [PAI]: Como agora meu filho terminou, vou encerrar também! \n");
        sleep(sec);
    }

    // Se o ID retornado da chamada for IGUAL a zero (0), então estamos no processo FILHO
    else if (id == 0){
        /*
            O código aqui é executado pelo processo FILHO.
            É exibido em tela algumas informações que identifique isso, como: 
            PID do FILHO, PID do PAI do processo FILHO, espaço de endereçamento usado ao 
            manipular "num" (mesmo que o PAI) e o valor dele após alteração.
        */
        printf(" [FILHO]: Meu PID é -> %i \n", getpid());
        printf(" [FILHO]: Meu Pai tem PID -> %i \n", getppid());

        /* 
            Soma realizada para alterar valor de "num" e termos um comparativo
            de que a alteração dele pelo processo FILHO não afeta o valor de "num" que está sendo 
            processado pelo PAI.
        */
        num += 10;
        printf(" [FILHO]: Usei a posicao '%p', mas meu numero é: %i \n", &num, num);

        // Espera alguns segundos e sinaliza o encerramento do processo FILHO
        printf(" [FILHO]: Vou dormir por %i segundos antes de encerrar \n", sec);
        sleep(sec);
        printf(" [FILHO]: Encerrando... \n");
    }

    /* 
        Se o ID retornado da chamada for diferente disso, ou seja, MENOR que zero (0), 
        então não foi possivel executar o fork() e o novo processo (filho) não foi criado.
    */
    else{
        printf("Falha: não foi possivel executar o fork() ! \n");
        exit(1);
    }

    return 0;
}
