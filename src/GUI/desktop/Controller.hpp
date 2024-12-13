#pragma once
#include <QObject>

#include "../../backend/SlotMachine.hpp"
#include "View.hpp"

class SlotMachineController : public QObject {
  Q_OBJECT

 public:
  SlotMachineController(SlotMachine *model, SlotMachineView *view);
  ~SlotMachineController() override;

 public slots:
  void startGame();
  void stopGame();

 private:
  SlotMachine *model_;
  SlotMachineView *view_;
  Action action = Action::NoAction;

  void ProcessingUserInput();
  void UpdateView();
};