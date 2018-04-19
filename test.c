#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int file_read();
void file_write(uint8_t buffer);

int main() {
  FILE * pFilein, *pFileout;
  uint8_t buffer = 0;

  pFilein = fopen("moeller.raw", "r");
  pFileout = fopen("bajer.raw", "w");

  if(pFilein == NULL) {
    fputs("Error opening input file\n", stderr);
    exit(1);
  }

  while(feof(pFilein) == 0) {
    fread(&buffer, 1, 1, pFilein);
    fwrite(&buffer, 1, 1, pFileout);
  }

  fclose(pFilein);
  fclose(pFileout);
  return 0;
}

int file_read() {
  uint8_t buffer;
  FILE * pFilein;

  pFilein = fopen("moeller.raw", "rb");
  if (pFilein == NULL)
  {
    fputs("Failed to open file\n.", stderr);
    exit(1);
  }
  fread(&buffer, 1, 1, pFilein);
  return buffer;
}

void file_write(uint8_t buffer)
{
  FILE * pFileout;
  pFileout = fopen("bajer.raw", "wb");

  if (pFileout == NULL)
  {

  }



}
