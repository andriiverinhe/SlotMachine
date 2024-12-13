#include "Controller.hpp"

#include <QTimer>

SlotMachineController::SlotMachineController(SlotMachine *model,
                                             SlotMachineView *view)
    : model_(model), view_(view) {
  connect(view_->startButton_, &QPushButton::clicked, this,
          &SlotMachineController::startGame);
  connect(view_->stopButton_, &QPushButton::clicked, this,
          &SlotMachineController::stopGame);

  // QTimer *timerForUpdate = new QTimer(this);
  // timerForUpdate->setInterval(50);

  // connect(timerForUpdate, &QTimer::timeout, this,
  //         &SlotMachineController::UpdateView);

  // timerForUpdate->start();

  QTimer *timerForUserInput = new QTimer(this);
  timerForUserInput->setInterval(100);

  connect(timerForUserInput, &QTimer::timeout, this,
          &SlotMachineController::ProcessingUserInput);

  timerForUserInput->start();
}

SlotMachineController::~SlotMachineController() {}

void SlotMachineController::startGame() { model_->UserInput(Action::Start); }
void SlotMachineController::stopGame() { model_->UserInput(Action::Stop); }

void SlotMachineController::ProcessingUserInput() {
  model_->UserInput(this->action);
  this->action = Action::NoAction;
  this->UpdateView();
}

void SlotMachineController::UpdateView() {
  if (model_) view_->updateView(model_->getGameInfoForUpdateView());
}