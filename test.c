#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
<<<<<<< HEAD

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
=======
  FILE * pFilein, *pFileout;
  uint8_t buffer = 0;
>>>>>>> refs/remotes/origin/master

  pFilein = fopen("moeller.raw", "r");
  pFileout = fopen("bajer.raw", "w");

  if(pFilein == NULL) {
    fputs("Error opening input file\n", stderr);
    exit(1);
  }
<<<<<<< HEAD
  printf("Trying to read from file.\n");
  fread(&buffer, 1, 1, pFilein);
  return buffer;
}

void file_write(uint8_t buffer)
{
  pFileout = fopen("bajer.raw", "wb");
=======
>>>>>>> refs/remotes/origin/master

  while(feof(pFilein) == 0) {
    fread(&buffer, 1, 1, pFilein);
    fwrite(&buffer, 1, 1, pFileout);
  }
<<<<<<< HEAD
  printf("Trying to write to file.\n");
  fwrite(&buffer, 1, 1, pFileout);
  return;
=======

  fclose(pFilein);
  fclose(pFileout);
  return 0;
>>>>>>> refs/remotes/origin/master
}
