#include <stdio.h>

int main(void)
{
    int i, j;

    printf("Tabela ASCII\n");

    printf("%c", 201);
    for(i=0; i<=100; i++)printf("%c",205);
    printf("%c",187);
    printf("\n");

    for(i = 48; i <= 247;)
    {
        for(j = 0; j < 10 && i <= 247; j++)
        {
            if (j == 0)
            {
                printf("%c %3d = %-3c ", 186,i, i);
            }
            else if (j == 9 || i == 247)
            {
                printf("%3d = %-3c %c", i, i, 186);
            }
            else
            {
                printf("%3d = %-3c ", i, i);
            }

            i++;
        }
        printf("\n");
    }

    printf("%c", 200);
    for(i=0; i<=100; i++)printf("%c",205);
    printf("%c",188);
    printf("\n");

    return 0;
}
