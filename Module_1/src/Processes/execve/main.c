#include <stdio.h>
#include <unistd.h>

/*
    Arquivo principal feito para ilustrar o funcionamento do "execve"
    Observe que foi pré-estabelecido o caminho do programa e o parametro.
    que será passado na execução do mesmo.
*/

int main(int argc, char const *argv[])
{

    // Caminho onde está o novo programa
    char pathname[] = "./novo";

    /* 
       Parametro passado para a execução do novo processo.
       Foi fixado "Ola Mundo", mas poderia ser qualquer String.
       Caso não se queira passar um parâmetro ao novo processo, pode-se deixar NULL nos argumentos.
    */
    char param[] = "Ola Mundo";
    
    /* 
        Definição dos argumentos que serão passados ao novo processo.
        Caso não se queira passar um parâmetro ao novo processo, pode-se deixar NULL.
        O NULL ao final do vetor é necessário pois indica o momento em que se chegou ao fim.
    */
    char * arg[] = {pathname, param, NULL};

    // Print para ilustrar a tentativa de execução do novo processo (aguarda 3 segundos)
    printf(" Tentando executar pathname: %s \n\n", pathname);
    sleep(3);

    /* 
        Executa a chamada de sistema execve para trocar o processo em execução pelo novo.
        Nenhum retorno normalmente é esperado. Se houver retorno (valor -1) é porque algo deu errado.
        "__environ" define um vetor com as variáveis de ambiente terminada em NULL
        Parametros doe execve:
            - caminho do novo programa
            - lista de possiveis argumentos para o novo programa
            - ambiente de usuario onde o novo processo irá executar
    */
    if (execve(pathname, arg, __environ) == -1 ) {
        printf(" Algo deu errado na execucao do execve! \n");
    }
    
    /*
        Se não houver retorno algum, o novo processo foi executado e encerrado. 
        Se deu tudo der certo (o que é o esperado) o processo em execução foi trocado pelo novo
        e esses últimos prints não foram exibidos em tela (não foram executados).
    */
    printf("--------------------------------------------------------------\n");
    printf(" Se o execve der certo, esse print nao devera aparecer !!! \n");
    printf("--------------------------------------------------------------\n");

    return 0;
}
