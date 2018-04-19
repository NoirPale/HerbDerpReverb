#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t file_read(FILE * pFilein);
void file_write(FILE * pFileout, uint8_t buffer, float decay, uint16_t delay);

int Huff[44101] = { 0 };
uint8_t buffer = 0;


int main() {

  uint8_t buffer;
  FILE * pFilein;
  FILE * pFileout;

  pFilein = fopen("moeller.raw", "r");
  if (pFilein == NULL)
  {
    fputs("Failed to open file\n.", stderr);
    exit(1);
  }

  pFileout = fopen("bajer.raw", "w");
  if (pFileout == NULL)
  {
    fputs("Error opening output file\n", stderr);
    exit(1);
  }

  while (feof(pFilein) == 0)
  {
    buffer = file_read(pFilein);
    file_write(pFileout, buffer, 0.05, 150);
  }

  fclose(pFilein);
  fclose(pFileout);
  return 0;
}

uint8_t file_read(FILE * pFilein) {
  uint8_t buffer;
  fread(&buffer, 1, 1, pFilein);
  return buffer;
}

void file_write(FILE * pFileout, uint8_t buffer, float decay, uint16_t delay)
{
  int layS = ((float)delay * 44.1f);
  uint16_t iter = 0;

  buffer += *(Huff + iter);
  *(Huff + iter) = (decay * buffer);
  iter++;

  if (iter == (layS + 1))
  {
    printf("pølse.raw.\n");
    iter = 0;
  }

  fwrite(&buffer, 1, 1, pFileout);
}
