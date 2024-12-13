#include <QApplication>

#include "../../backend/SlotMachine.hpp"
#include "Controller.hpp"
#include "View.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  SlotMachine model;
  SlotMachineView view;
  SlotMachineController controller(&model, &view);

  view.show();
  view.update();

  return app.exec();
}