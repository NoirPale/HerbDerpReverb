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
int Puff[2];
/*****************************   Functions   *********************************
 *   Function : See General module specification (general.h-file).
 *****************************************************************************/

int ReadRaw(int state)
{
    FILE *stick;
    int answer = 1;
    if (state)
    {

        stick = fopen("moeller.raw", "rb");
        if(stick == NULL)
            printf("Failed to open file moeller.raw.\n");

        fread(Puff, 1, 1, stick);
        if (feof(stick) > 0)
        {
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
    FILE *pout;

    if (state)
    {
        pout = fopen("bajer.raw", "wb");
        if (pout == NULL)
            printf("Failed to open file bajer.raw.\n");

        fwrite(Puff, 1, 1, pout);
    }
    else
    {
        fclose(pout);
    }
}

void ReDerp(int *Huff, int *Puff, float delay, int decay)
{
    int layS = (delay * 44.1f); // assumes 44100 Hz sample rate
    static uint16_t iter = 0;
    if (iter == 0)
    {
        Puff[0] += Huff[layS];
    }
    else
    {
        Puff[0] += Huff[iter - 1];
    }
    Huff[iter] = (decay * Puff[0]);
    iter++;
    if (iter == (layS + 1))
    {
        iter = 0;
    }
}

int main(void)
{

    int delay = 250;
    float decay = -0.25f;
    while (ReadRaw(1))
    {
        ReDerp(Huff, Puff, delay, decay);
        WRaw(1);
    }
    ReadRaw(0);
    WRaw(0);
    return 0;
}

/****************************** End Of Module *******************************/
