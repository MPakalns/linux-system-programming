/*

Uzdevuma formulējums.

Programma kas taisa N pavedienus, kur katrs izdrukā M burtus.
N un M ir parametri. Drukājamais burts ir katram pavedienam atšķirīgs.
Testēt un novērot gan kādā kārtībā burti tiek drukāti, gan kopējo burtu skaitu.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Struktūra, kas glabā thread funkcijai (printLetters) padodamo argumentu vērtības
typedef struct
{
    int numberOfLetters;
    char letter;
} ThreadArguments;

void* printLetters(void* arguments)
{
    ThreadArguments* localArguments = (ThreadArguments*) arguments;
    for (int i = 0; i < localArguments->numberOfLetters; i++)
    {
        printf("%c", localArguments->letter);
    }
    printf("\n");
}

// "argc" ir komandrindas padoto argumentu skaits, bet "argv" satur to vērtības
int main(int argc, char *argv[])
{   
    // --- Padoto argumentu apstrādes daļa ---

    // Pašas programmas izpildes komanda skaitās kā arguments, tāpēc plus viens
    int neededArgumentCount = 2;
    neededArgumentCount++;

    // n - pavedienu skaits, m - burtu skaits
    int n = 0;   
    int m = 0;

    if (argc != neededArgumentCount)
    {
        printf("ERROR: Not the right ammount of arguments passed! \n");
        return 1;
    }

    char* endPointer = NULL;

    n = strtol(argv[1], &endPointer, 10);
    // Nav atrasti cipari vai aiz cipariskām vērtībām seko ne-cipariskas vērtības
    if (endPointer == argv[1] || *endPointer != '\0') 
    {
        printf("ERROR: Argument 'N' is invalid!\n");
        return 1;
    }

    m = strtol(argv[2], &endPointer, 10);
    // Nav atrasti cipari vai aiz cipariskām vērtībām seko ne-cipariskas vērtības
    if (endPointer == argv[1] || *endPointer != '\0') 
    {
        printf("ERROR: Argument 'M' is invalid!\n");
        return 1;
    }

    // --- Saturīgā daļa ---

    pthread_t* threadIDs = (pthread_t*)malloc(n * sizeof(pthread_t));
    ThreadArguments* arguments_array = malloc(n * sizeof(ThreadArguments));

    // Pavedienu izveidošana
    for (int i = 0; i < n; i++)
    {
        ThreadArguments arguments = {m, 'a' + i};
        arguments_array[i] = arguments;

        if (pthread_create(&(threadIDs[i]), NULL, printLetters, (void*)&arguments_array[i]) != 0) 
        {
            // "Nogalināt" visu programmu ir drošāk un jēdzīgāk
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Paveidienu savienošana
    for (int i = 0; i < n; i++)
    {
        if (pthread_join(threadIDs[i], NULL) != 0) 
        {
            // "Nogalināt" visu programmu ir drošāk un jēdzīgāk
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}