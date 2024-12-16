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
  SlotMachine *_model;
  SlotMachineView *_view;
  Action _action = Action::NoAction;

  void ProcessingUserInput();
  void UpdateView();

  bool connectToBtn();

  bool createConnectWithTimer(const int &msec,
                              void (SlotMachineController::*func)());
};