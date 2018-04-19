#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
  FILE * pFilein, *pFileout;
  signed int Huff[44101] = { 0 };
  signed int buffer = 0;
  uint16_t iter = 0;
  float delay = 500, decay = -0.30;
  int layS = (delay * 44.1f);

  pFilein = fopen("moeller.raw", "r");
  pFileout = fopen("bajer.raw", "w");

  if(pFilein == NULL) {
    fputs("Error opening input file\n", stderr);
    exit(1);
  }
  while(feof(pFilein) == 0) {
    fread(&buffer, 1, 1, pFilein);
    buffer += *(Huff + iter);
        *(Huff + iter) = (decay * buffer);
        iter++;
        if (iter == (layS + 1))
        {
            iter = 0;
        }
    fwrite(&buffer, 1, 1, pFileout);
  }

  fclose(pFilein);
  fclose(pFileout);
  return 0;
}
