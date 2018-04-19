#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void file_read(FILE * pFilein);
void file_write(FILE * pFileout);
void echo_effect(float decay, uint16_t delay);

float Huff[44101] = { 0 };

FILE * pFilein;
FILE * pFileout;

int main() 
{
  pFilein = fopen("Dammmit.raw", "rb");
  if (pFilein == NULL)
  {
    fputs("Failed to open file\n.", stderr);
    exit(1);
  }

  pFileout = fopen("test.raw", "wb");
  if (pFileout == NULL)
  {
    fputs("Error opening output file\n", stderr);
    exit(1);
  }

  while (feof(pFilein) == 0)
  {
    echo_effect(0.25, 250);
  }

  fclose(pFilein);
  fclose(pFileout);
  return 0;
}
/*
void file_read(FILE * pFilein)
{
  fread(&buffer, 1, 1, pFilein);
}

void file_write(FILE * pFileout)
{
  fwrite(&buffer, 1, 1, pFileout);
}
*/
void echo_effect(float decay, uint16_t delay)
{ 
  float buffer; 
  static uint16_t iter;

  int layS = ((float) delay * 44.1f);

  fread(&buffer, 4, 1, pFilein);

  buffer += Huff[iter];
  Huff[iter] = (decay * buffer);
  iter++;

  if (iter == (layS + 1))
  {
    printf("pølse.raw.\n");
    iter = 0;
  }
  fwrite(&buffer, 4, 1, pFileout);
}

