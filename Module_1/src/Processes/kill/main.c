#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // Declaração de variável que receberá o ID de retorno do fork() na criação do novo processo
    pid_t id;

    /* 
        Declaração de variaveis utilizadas. Altere o valor se quiser.
        O "sec" é para estabelecer um sleep e acompanhar no console as execuções mais pausadamente.
    */
    int sec = 3;
    
    printf("------------------- \n");
    printf(" Iniciando execução \n");
    printf("------------------- \n");
    sleep(sec);

    // Criar um novo processo (fork) e recebe como retorno o pid_t da chamada de sistema
    id = fork();

    // Se o ID retornado da chamada for IGUAL a zero (0), então estamos no processo FILHO
    if (id == 0){
        /*
            O código aqui é executado pelo processo FILHO.
            É exibido em tela algumas informações que identifique isso, como: 
            PID do FILHO e PID do PAI do processo FILHO.
        */
        printf(" [FILHO]: Meu PID é -> %i \n", getpid());
        printf(" [FILHO]: Meu Pai tem PID -> %i \n", getppid());

        /*
            Exibe em tela indicação sobre o loop infitino implementado 
            para manter o processo sempre em execução (a menos que seja forçadamente encerrado)
        */
        printf(" [FILHO]: Vou ficar executando eternamente até me encerrarem (loop infinito) ! \n");
        for (;;);

    }

    // Se o ID retornado da chamada for MAIOR que zero (0), então estamos no processo PAI
    else if (id > 0){
        /*
            O código aqui é executado pelo processo PAI.
            É exibido em tela algumas informações que identifique isso, como: PID do PAI
        */
        printf(" [PAI]: Meu PID é -> %i \n", getpid());
        printf(" [PAI]: Vou esperar por %i segundos a execução de meu filho. \n", sec);
        sleep(sec);

        // Exibe em tela a indicação de que encerrará o processo FILHO
        printf(" [PAI]: Agora vou encerrar meu filho! \n");

        /* 
            Encerra o processo filho enviando sinal -9
            e aguarda para seguir em frente com seu proprio encerramento.
        */
        kill(id, SIGKILL);
        wait(NULL);
        
        // Exibe em tela que o processo pai também terminará sua execução.
        printf(" [PAI]: Como agora finalizei meu filho, vou encerrar também! \n");
        sleep(sec);

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
