#include "types.h"
#include "user.h"

int
main(void)
{
  for (int i = 0; i < 256; i++){
      printf(1, "%c ", i);
      if ((i+1) % 16 == 0)
        printf(1, "\n");
  }
  exit();
}