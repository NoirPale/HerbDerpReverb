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
int Huff[22050] = {0};
int Puff[2];
/*****************************   Functions   *********************************
 *   Function : See General module specification (general.h-file).
 *****************************************************************************/

int ReadRaw(char * namae, int state)
{
    FILE *stick;
    int answer = 1;
    if (state)
    {

        stick = fopen(namae, "rb");
        fread(Puff, 2, 1, stick);
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

void WRaw(int * Smack, char * name, int state)
{
    if (state)
    {
        FILE *pout;
        pout = fopen(name, "wb");
        fwrite(Puff, 1, 1, name);
    }
    else
    {
        fclose(pout);
    }
}

void ReDerp(int *Huff, int *Puff, int delay, int decay)
{
    static int layS = (int) ((float) delay * 44.1f); // assumes 44100 Hz sample rate
    static uint16_t iter = 0;
    if (iter == 0)
    {
        Puff[0] += Huff[layS]
    }
    else
    {
        Puff[0] += Huff[iter - 1]
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
    while(ReadRaw("moeller.raw",1))
    {
    ReDerp(Huff, Puff, delay, decay);
    WRaw("bajer.raw",1);
    }
    ReadRaw("moeller.raw", 0);
    WRaw("bajer.raw",0);
    return 0;
}

/****************************** End Of Module *******************************/
