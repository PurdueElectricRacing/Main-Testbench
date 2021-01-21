#include "pervertt_main_frame.h"
#include "can_interface.hpp"

#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
  std::cout << "Creating CAN Objects.\n";
  CanInterface canable;
  CanFrame frame;
  while (true)
  {
    std::cout << "Reading from CAN Bus.\n";
    frame = canable.readCanData();
    std::cout << frame << "\n";
  }

  QApplication a(argc, argv);
  PERVERTT_MAIN_FRAME w;
  w.show();
  return a.exec();
}
