#include <stdio.h>

//Parametros padrao: quantidade de argumentos e vetor de argumentos
int main(int argc, char const *argv[])
{

    // Print de ilustracao para indicar que este arquivo foi executado
    printf(" ----------------------------- \n");
    printf(" Arquivo novo foi executado! \n");

    // Se quantidade de argumentos validos informados for apenas 1,
    //printa que nao foi informado mais parametros ao novo programa
    if (argc != 2){
        printf(" Nenhum parametro foi informado! \n");
    }
    // Se alem do nome do programa (argv[0]), tambem foi informado um segundo parametro, 
    //printa 2º parametro (argv[1])
    else{
        printf(" Parametro informado: %s \n", argv[1]);
    }

    printf(" ----------------------------- \n");

    return 0;
}


