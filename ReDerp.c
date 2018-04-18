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

/*****************************   Functions   *********************************
 *   Function : See General module specification (general.h-file).
 *****************************************************************************/
int Puff;

void ReadRaw(char * name, int state)
{
    if(state)
    {
    FILE *p_in;
    p_in = fopen(name, "rb");

    }
    else
    {
    fclose(p_in);
    }
}

void WRaw(int * Smack, char * name, int state)
{
    if(state)
    {
    FILE *p_out;
    p_out = fopen(name, "wb");

    }
    else
    {
    fclose(p_in);
    }
}

void ReDerp(int *Puff)
{
    int delay = 500; // half a second
        int delaySamples = (int) ((float) delay * 44.1f); // assumes 44100 Hz sample rate
        float decay = 0.5f;
        for (int i = 0; i < buffer.length - delaySamples; i++)
        {
            // WARNING: overflow potential
            fread(buffer, 2, 1, p_in);
            buffer[i + delaySamples] += (short) ((float) buffer[i] * decay);
        }
}

int main(void)
{
    int Puff;

    int buffer[22050];
    fread(buffer, )
    int delay = 500; // half a second
    int delaySamples = (int) ((float) delay * 44.1f); // assumes 44100 Hz sample rate
    float decay = 0.5f;
    for (int i = 0; i < buffer.length - delaySamples; i++)
    {
        // WARNING: overflow potential
        fread(buffer, 2, 1, p_in);
        buffer[i + delaySamples] += (short) ((float) buffer[i] * decay);
    }

    fclose(p_in);
    fclose(p_out);

    return 0;
}

/****************************** End Of Module *******************************/
