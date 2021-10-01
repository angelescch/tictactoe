#include "types.h"
#include "user.h"

int
main(void)
{
  modeswitch(1);
  for (int y = 0; y < 16; y++){
    for (int x = 0; x < 16; x++){
        plotrectangle(x*10, y*10, x*10+10, y*10+10, y*10+x);
    }
  }
  sleep(200);
  modeswitch(0);
  exit();
}
