#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>

// target to hit so that no while can get out of the loop
bool threadFim = false;

//mutex is used for the program's threads so there can be an organization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//A struct was defined for structuring the inserted data
typedef struct info
{ 
    int indice;
    int salto_Max;
    int tamanho_da_pista;
} infoValores;


void *funcaoThread(void *valor)
{

    infoValores *vetor = (infoValores *)valor;
    int distanciaPercorrida = 0;

    srand(time(NULL));

    while (true)
    {
        /* use of rand function to randomly generate each thread a different jump value */
        int salto_realizado = rand() % (vetor->salto_Max - 10) + 10;

            /* mutex is used to organize the critical section in sharing with multiple threads simultaneously */
            pthread_mutex_lock(&mutex);

        // according to the jumps performed we have increased the distance covered
        distanciaPercorrida += salto_realizado;
        printf("A lebre %d | ", vetor->indice);
        printf("saltou %d cm | ", salto_realizado);
        printf("total %d\n\n", distanciaPercorrida);

        if (distanciaPercorrida >= vetor->tamanho_da_pista) // once the size is reached
        {   
            printf("A lebre %d foi a ganhadora ", vetor->indice); // we display the winner index
          
            printf("\n\nFim da corrida de lebres\n\n");
            printf("\n======================================\n");
            break;
        }
            pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    free(valor);
    exit(EXIT_SUCCESS);
}

int funcaoProcesso(infoValores vetor)
{
    /* the distance traveled starts at 0 then we have
    the values incremented through the while until reaching the condition which is the track size*/
    int distanciaPercorrida = 0;
    srand(time(NULL));

    while (true)
    {
        //it uses rand for random values of the jumps performed
        int salto_realizado = rand() % (vetor.salto_Max - 10) + 10;
        distanciaPercorrida += salto_realizado;

        //it takes the values of the lengths performed and the distance traveled by each process
        printf("A lebre %d"" | ", vetor.indice);
        printf("saltou %d cm"" | ", salto_realizado);
        printf("total %d\n" "", distanciaPercorrida);

        if (distanciaPercorrida >= vetor.tamanho_da_pista)
        { // when the first process reaches the value of the distance entered, it's printed the winning thread/process
            printf("\n\nA lebre %d foi a ganhadora\n\n", vetor.indice);
            printf("\n\nFim da corrida de lebres\n\n");
            printf("\n======================================\n");
            break;
            exit(EXIT_SUCCESS);
        }

        sleep(2);
    }

    
    return 0;
}

int main(int quantidade_Arg, char *listaArg[]) 
// one of the first parts implemented was the use of Ar for the 3 main parameters

{

    printf("\n======================================\n");

    for (int i = 1; i < quantidade_Arg; i++)
    { //it's used the for to print the entered parameters
        printf("%d | Dados do parametro : %s\n", i, listaArg[i]);
    }
    printf("\n\n======================================\n");
    printf("Comecou a corrida de lebres");
    printf("\n\n\n");
    

    if (strcmp(listaArg[1], "-t") == 0) // the first parameter Arg[1] and the -t for threads
      
    {
        printf("Foi escolhido Threads\n\n");

        pthread_t thread[atoi(listaArg[2])]; 
        // get the value convert to integer and so we define the amount of threads to be created
        
       
        int identificador;
        int numero_Lebre;

        for (int i = 0; i < atoi(listaArg[2]); i++)
        {  
            // malloc is used to allocate memory on the heap, so there is no interference between the threads's data
          
            infoValores *vetor = malloc(sizeof(infoValores)); 
            vetor->indice = i;
            vetor->salto_Max = 20;
            vetor->tamanho_da_pista = atoi(listaArg[3]);

            identificador = pthread_create(&thread[i], NULL, funcaoThread, (void *)vetor);
            // We use a flag as identified
        }

        for (int i = 0; i < atoi(listaArg[2]); i++)
        {   
            void *retorno;
            identificador = pthread_join(thread[i], &retorno);

            /* pthread_join takes the thread's control structure as arguments.
            It makes the calling thread wait until the created thread have done your job */
            int *valorRetorno = (int *) retorno;


           if (*valorRetorno != -1){
               break; 
           }   
            
        }
    }

    else if (strcmp(listaArg[1], "-p") == 0) 
      // when the parameter is p
      
    {
        // the variable keep the getpid value 
        pid_t processoPID = getpid();
        int fork_processo;
        int status;

        printf("Foi escolhido processos\n\n");

        for (int i = 1; i <= atoi(listaArg[2]); i++)
        {
            if (processoPID == getpid())
            {
                fork_processo = fork();
                if (fork_processo == 0) 
                {   // If the fork function returns 0 (zero), the child process is running

                    // Dynamically allocate the values
                    infoValores *vetor = malloc(sizeof(infoValores));
                    vetor->indice = i;
                    vetor->salto_Max = 20;
                    vetor->tamanho_da_pista = atoi(listaArg[3]);

                    int retorno = funcaoProcesso(*vetor);
                    return retorno;
                }
                
            }
        }

        if (processoPID = getpid()){ 
            // it's used the getpid value so that in the end we can kill all processes using kill 0
            
            wait(&status);
            kill(0, SIGKILL);
            int retornoFilho = WEXITSTATUS(status);
        
        }
    
    }
    return 0;
}