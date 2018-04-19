/*****************************************************************************
 * University of Southern Denmark
 * Embedded Programming (EMP)
 *
 * MODULENAME.: ReDerp.c
 *
 * PROJECT....: HerbDerpReverb
 *
 * DESCRIPTION: See module specification file (.h-file).
 *
 * Change Log:
 ******************************************************************************
 * Date			Id	  Change
 * MMM DD, YYYY
 * ----------------------------------------------------------------------------
 * Apr 18, 2018	SoF   Module created.
 *
 *****************************************************************************/

/***************************** Include files ********************************/
#include <stdio.h>
#include <stdint.h>
/*****************************    Defines    ********************************/

/*****************************   Constants   ********************************/

/*****************************   Variables   ********************************/
int Huff[22050] = { 0 };
int Puff[100];
/*****************************   Functions   *********************************
 *   Function : See General module specification (general.h-file).
 *****************************************************************************/

int ReadRaw(int state)
{
    static int virgin = 1;
    FILE *stick;
    int answer = 1;
    if (virgin)
    {
        stick = fopen("moeller.raw", "rb");
        if (stick == NULL)
            printf("Failed to open file moeller.raw.\n");
        virgin = 0;
    }
    if (state)
    {

        fread(Puff, 1, 1, stick);
        printf("%d %d %d %d.\n", Puff[0], Puff[1], Puff[2], Puff[3]);
        if (feof(stick) > 0)
        {
            printf("Going in VASA-Style.\n");
            answer = 0;
        }
    }
    else
    {
        fclose(stick);
    }
    return answer;
}

void WRaw(int state)
{
    static int iter = 0;
    int fuck_off[600000];
    static int touched_for_the_very_first_time = 1;
    FILE *pout;
    if (touched_for_the_very_first_time)
    {
        pout = fopen("bajer.raw", "wb");
        if (pout == NULL)
            printf("Failed to open file bajer.raw.\n");
        touched_for_the_very_first_time = 0;
    }
    if (state)
    {
        fuck_off[iter]  = *Puff;
        printf("Not soggy condom\n");
        ++iter;
    }
    else
    {
        printf("soggy condom\n");
        fwrite(fuck_off, 1, iter, pout);
//        fputc(*fuck_off, pout);
        printf("Hele molevitten.\n");
        fclose(pout);
    }
    printf("Wraw complete\n");
}

void ReDerp(int *Huff, int *Puff, float delay, float decay)
{
    int store;
    int layS = (delay * 44.1f); // assumes 44100 Hz sample rate
    static uint16_t iter = 0;
    *Puff += *(Huff + iter);
    store = *Puff;
    *(Huff + iter) = (decay * store);
    iter++;
    if (iter == (layS + 1))
    {
        printf("pølse.raw.\n");
        iter = 0;
    }
    printf("Why you no WORK %d Rød bil %d Gul bil %d Post Bil %d Felt madress.\n", *(Huff + 1), *(Huff), *(Puff), iter);
}

int main(void)
{

    float delay = 250;
    float decay = 0.25f;
    int crap;
    crap = ReadRaw(1);
    while (crap)
    {
        ReDerp(Huff, Puff, delay, decay);
        WRaw(1);
        printf("it reached wraw");
        crap = ReadRaw(1);
        printf("Loop deLoop.\n");
    }
    printf("Impregnation done.\n");
    ReadRaw(0);
    WRaw(0);
    return 0;
}

/****************************** End Of Module *******************************/
