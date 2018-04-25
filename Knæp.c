#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
  FILE * pFilein, *pFileout;
  float Huff[44101] = { 0 };
  float buffer = 0;
  uint16_t iter = 0;
  float delay = 150, decay = -0.2;
  int layS = (delay * 44.1f);

  pFilein = fopen("a_floater.raw", "r");
  pFileout = fopen("damn.raw", "w");


  if(pFilein == NULL) {
    fputs("Error opening input file\n", stderr);
    exit(1);
  }
  while(feof(pFilein) == 0) {
    fread(&buffer, 4, 1, pFilein);
    buffer += *(Huff + iter);
        *(Huff + iter) = (buffer * decay);
        iter++;
        if (iter == (layS + 1))
        {
            iter = 0;
        }
    fwrite(&buffer, 4, 1, pFileout);
  }

  fclose(pFilein);
  fclose(pFileout);
  return 0;
}
