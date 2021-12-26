#include <CModemManager.h>
#include <iostream>
int main()
{
  oFonoIntegration::CModemManager modemManager;
  std::cout << "Starting" << std::endl;
  modemManager.Initialize();

  std::cout << "Almost end" << std::endl ;
  while(1) {};
  return 0;
}
