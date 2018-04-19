#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int file_read();
void file_write(uint8_t buffer);

FILE * pFilein;
FILE * pFileout;

int main() {

  uint8_t buffer;
  printf("entering while loop.\n");
  while(feof(pFilein) == 0)
  {
    buffer = file_read();
    file_write(buffer);
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
  printf("Trying to read from file.\n");
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
  printf("Trying to write to file.\n");
  fwrite(&buffer, 1, 1, pFileout);
  return;
}
