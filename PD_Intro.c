/*

Uzdevuma formulējums.

1. Uzrakstīt funkciju int sv_garums(char *virkne), kas atrod simbolu virknes garumu.
Šeit un turpmāk var pieņemt, ka simbolu virknes korekti beidzas ar nulles simbolu (C kodā pierakstāms kā '\0', vai arī vienkārši 0).

2. Uzrakstīt funkciju void sv_kopet(char *no, char *uz), kas nokopē simbolu virkni.
Var pieņemt, ka vietas pietiks.
Izaicinājums – neizmantot papildus mainīgos!

3. Uzrakstīt funkciju int sv_meklet(char *kur, char *ko).
Funkcija sameklē un atgriež simbolu skaitu no virknes "kur" sākuma līdz vietai, kur tajā pirmoreiz atrodama virkne "ko".
Ja "ko" nav atrodams virknē "kur", tad atgriež -1.
sv_meklet("to be or not to be", "be") -> 3.
sv_meklet("something else", "be") -> -1.

4. Uzrakstīt funkciju void sv_apgriezt(char *virkne), kas apgriež simbolu virkni.
Piemērs: "abcd" -> "dcba".
Izmantotās papildus atmiņas apjomam jābūt neatkarīgam no simbolu virknes garuma!

5. (Neobligāts) Uzrakstīt funkciju void sv_vapgriezt(char *virkne), kas apgriež vārdus simbolu virknē.
Piemērs: "hello world" -> "world hello".
Izmantotās papildus atmiņas apjomam jābūt neatkarīgam no simbolu virknes garuma!

*/

#include <stdio.h>

int sv_garums(char *virkne)
{
    int garums = 0;
    int turpinat = 1;
    while (turpinat == 1)
    {
        if (*(virkne+garums) == '\0')
        {
            turpinat = 0;
        }

        else
        {
            garums++;
        }
    }

    return garums;
}
 
void sv_kopet(char *no, char *uz)       // Bez papildus mainīgajiem :)
{
    *uz = *no;
    while (1)
    {
        if (*no != '\0')
        {
            *uz = *no;
            *uz++;
            *no++;
        }

        else break;
    }
}

int sv_meklet(char *kur, char *ko)
{
    int kurGarums = sv_garums(kur);
    int koGarums = sv_garums(ko);
    int lidzGarums = 0;
    int indekss = 0;

    // Ja "ko" ir garāks par "kur", tad tas nemaz neietilps iekš "kur" - tātad nav jēgas meklēt
    if (koGarums > kurGarums) return -1;

    // Šis gadījums ir mazliet filozofisks, proti, atgriezt -1 vai 0?
    // Ja mēs simbolu virkni uztveram kā masīvu, tad šajā gadījumā "kur" un "ko" masīvi ir garumā 1, jo satur tikai '\0'.
    // Sākuma indekss ir nulle, mēs atrodamies pirms pirmā simbola (abos masīvos).
    // Mēs pavirzāmies par vienu simbolu uz priekšu (abos masīvos).
    // Konstatējam, ka masīva "kur" un "ko" esošais apskatāmais simbols sakrīt, turklāt apakšvirkne "ko" ir garumā 1,
    // tāpēc tālāk skatīties nav nepieciešams. Esam atraduši apakšvirkni "ko" iekš virknes "kur".
    // Sanāk, ka no sākuma pozīcijas (pirms pirmā simbola) līdz atrastās apakšvirknes pozīcijai (pirmajam simbolam)
    // attālums ir nulle, tāpēc tiek atgriezts "0", nevis -1. 
    else if (*kur == '\0' && *ko == '\0') return 0;

    while (*kur != '\0')
    {
        if (*kur == *(ko + indekss))
        {
            if (*(ko + indekss) != '\0') indekss++;
        }

        else
        {
            indekss = 0;
        }

        lidzGarums++;
        *kur++;

        if (indekss == koGarums) return (lidzGarums - indekss);
    }

    return -1;
}

void sv_apgriezt(char *virkne)
{
    int virknesGarums = sv_garums(virkne);
    int apmainasPozicijas = virknesGarums / 2;
    
    int indekss = 0;
    while (indekss < apmainasPozicijas)
    {
        char tmp = *(virkne+indekss);
        *(virkne+indekss) = *(virkne+(virknesGarums-1)-indekss);
        *(virkne+(virknesGarums-1)-indekss) = tmp;

        indekss++;
    }
}

void sv_vapgriezt(char *virkne)
{
    char buf[sv_garums(virkne)+1];
    int vardaGarums = 0;
    int indekss = (sv_garums(virkne));

    while (*virkne != '\0')
    {
        if ((*(virkne+indekss) >= 65 && *(virkne+indekss) <= 90) || (*(virkne+indekss) >= 97 && *(virkne+indekss) <= 122))
        {
            vardaGarums++;
        }

        else
        {
            if (vardaGarums >= 0)
            {
                for (int i = 0; i < vardaGarums; i++)
                {
                    buf[sv_garums(virkne)-indekss+i] = *(virkne+indekss-(vardaGarums+i));
                }
            }
            vardaGarums = 0;
        }
        
        indekss++;
    }

    sv_kopet(buf, virkne);
}

int main(void) 
{
    char buferis[100];

    printf("Tests uzdevumam PD1.1:\n");
    printf("%d\n", sv_garums("hello world"));
    printf("%d\n", sv_garums("123"));
    printf("%d\n", sv_garums(""));

    printf("Tests uzdevumam PD1.2:\n");
    char teikums[12];                     // "Hello world" (11) + "\0" (1) = 12
    sv_kopet("hello world", teikums);
    printf("%s\n", teikums);
    char teikums2[4];                     // "123" (3) + "\0" (1) = 4
    sv_kopet("123", teikums2);
    printf("%s\n", teikums2);
    char teikums3[1];                     // "" (0) + "\0" (1) = 1
    sv_kopet("", teikums3);
    printf("%s\n", teikums3);

    printf("Tests uzdevumam PD1.3:\n");
    printf("Expected results: 13 32 0 3 0 0 -1 -1\n");
    printf("%d\n", sv_meklet("Ja banans ir dzeltens, tad to var est.", "dzeltens"));        // 13
    printf("%d\n", sv_meklet("a ab ab cd d abc abc bcd ab a a abcdabcd ab ab", "abcd"));    // 32
    printf("%d\n", sv_meklet("a", "a"));                                                    // 0
    printf("%d\n", sv_meklet("abc def", " "));                                              // 3
    printf("%d\n", sv_meklet(" ", " "));                                                    // 0
    printf("%d\n", sv_meklet("", ""));                                                      // 0
    printf("%d\n", sv_meklet("abc", "abcdef"));                                             // -1
    printf("%d\n", sv_meklet("abc", "z"));                                                  // -1

    printf("Tests uzdevumam PD1.4:\n");
    printf("Dots: abcd\n");
    sv_kopet("abcd", buferis);
    sv_apgriezt(buferis);
    printf("%s%s\n","Atgriezts: ", buferis);
    printf("Dots: 12345\n");
    sv_kopet("12345", buferis);
    sv_apgriezt(buferis);
    printf("%s%s\n","Atgriezts: ", buferis);
    printf("Dots: a   b c\n");
    sv_kopet("a   b c", buferis);
    sv_apgriezt(buferis);
    printf("%s%s\n","Atgriezts: ", buferis);

    // Diemžēl kaut kas nesanāca :(
    printf("Tests uzdevumam PD1.5:\n");
    sv_kopet("es eju pa ielas kreiso pusi", buferis);
    sv_vapgriezt(buferis);
    printf("%s\n", buferis);

    return 0;
}