/*

Uzdevuma formulējums.

Realizēt efektīvu failu kopēšanas programmu.

Brīva izvēle, kādas funkcijas vai sistēmas izsaukumus lietot. Ja lieto C bibliotēkas iebūvēto buferēšanu, bufera izmērs jāuzstāda atšķirīgs no noklusētā!

Programma pieņem divus argumentus: ieejas un izejas failu vārdi.
Ja izejas fails eksistē, tad jāuzprasa apstiprinājums, - vai tiešām to pārrakstīt?
Veiksmīgas, pilnas faila nokopēšanas gadījumā programmai jābeidzas ar izejas kodu 0, pretējā gadījumā ar: kodu -1, 
piemēram, ja ieejas fails nav atrasts, lasīšana neizdevās, izejas failu nevar izveidot vai nevar atvērt rakstīšanas režīmā, rakstīšana tajā neizdevās u.c. problēmas.

*/

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <stdio.h>

int exists(char *file_name)
{
    FILE* file;
    if ((file = fopen(file_name, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        return -1;
    }

    int fp = open(argv[1], O_RDONLY);
    int fp2;

    if (exists(argv[2]))
    {
        char answer = 'n';
        printf("The specified output file already exists. Do you want to overwrite it [y] or [n]?");
        scanf("%c", &answer);
        if (answer == 'y') { fp2 = open(argv[2], O_WRONLY); }
        else return -1;
    }

    else
    {
        fp2 = open(argv[2], O_WRONLY | O_CREAT, 0644);
    }

    if (fp < 0 || fp2 < 0) { return -1; }

    struct stat st;
    stat(argv[1], &st);
    size_t bufferSize = st.st_size;
    
    // Eksperimentēju dažādi, sākot no bufferSize 2048 līdz 8192*16, bet visu failu kopēt beigās tik un tā bija ātrāk nekā pa daļām
    if (sendfile(fp2, fp, 0, bufferSize) == -1) {  return -1; };
    return 0;
}