#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{

  modeswitch(1);
  plotrectangle(0,0,320,200,0x3F);
  printchar('h', 100, 100, 0x30, 3);
  

  sleep(200);
  modeswitch(0);
  exit();
}
