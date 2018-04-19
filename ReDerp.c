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
int Puff;
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
            printf("Failed to spread.\n");
        virgin = 0;
    }

    if (state)
    {

        fread(&Puff,1,1, stick);
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
    static int touched_for_the_very_first_time = 1;
    FILE *pout;
    if (touched_for_the_very_first_time)
    {
        pout = fopen("bajer.raw", "wb");
        if (pout == NULL)
            printf("Failed to lubricate.\n");
        touched_for_the_very_first_time = 0;
    }
    if (state)
    {
        printf("Trying to unscrew.\n");
        fwrite(&Puff, (size_t) 1, (size_t) 1, pout);
    }
    else
    {
        printf("soggy condom\n");
        fclose(pout);
    }
}

void ReDerp(int *Huff, int Puff, float delay, float decay)
{
    int layS = (delay * 44.1f); // assumes 44100 Hz sample rate
    static uint16_t iter = 0;
    Puff += *(Huff + iter);
    *(Huff + iter) = (decay * Puff);
    iter++;
    if (iter == (layS + 1))
    {
        printf("pølse.raw.\n");
        iter = 0;
    }
}

int main(void)
{

    float delay = 250;
    float decay = 0.25f;
    while (ReadRaw(1))
    {
        ReDerp(Huff, Puff, delay, decay);
        printf("ReDerp executed.\n");
        WRaw(1);
        printf("WRaw executed.\n");
        printf("Loop deLoop.\n");
    }


    printf("Impregnation done.\n");
    ReadRaw(0);
    WRaw(0);
    return 0;
}

/****************************** End Of Module *******************************/
