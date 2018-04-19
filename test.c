#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int file_read();
void file_write(uint8_t buffer);

FILE * pFilein;
FILE * pFileout;

int main() {
  while(feof(pFilein) == 0)
  {
    file_read();
    file_write(file_read());
  }

  fclose(pFilein);
  fclose(pFileout);
  return 0;
}

int file_read() {
  uint8_t buffer;

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
  pFileout = fopen("bajer.raw", "wb");

  if (pFileout == NULL)
  {
    fputs("Error opening output file\n", stderr);
    exit(1);
  }
  fwrite(&buffer, 1, 1, pFileout);
}
