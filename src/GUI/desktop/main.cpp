#include <QApplication>
#include <cstdlib>
#include <ctime>

#include "../../backend/SlotMachine.hpp"
#include "Controller.hpp"
#include "View.hpp"

int main(int argc, char *argv[]) {
  srand(static_cast<unsigned int>(time(0)));
  QApplication app(argc, argv);

  SlotMachine model;
  SlotMachineView view;
  SlotMachineController controller(&model, &view);

  return app.exec();
}