#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
  FILE * pFilein, *pFileout;
  int Huff[22050] = { 0 };
  uint8_t buffer = 0;
  uint16_t iter = 0;
  float delay = 250, decay = 0.25;
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
            printf("pølse.raw.\n");
            iter = 0;
        }
    fwrite(&buffer, 1, 1, pFileout);
  }

  fclose(pFilein);
  fclose(pFileout);
  return 0;
}
