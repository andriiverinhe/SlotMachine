#include "Controller.hpp"

#include <QCoreApplication>
#include <QMessageBox>
#include <QTimer>
#include <iostream>

bool SlotMachineController::connectToBtn() {
  auto startBtn = _view->getStartButton();
  auto stopBtn = _view->getStopButton();

  if (startBtn == nullptr || stopBtn == nullptr) return false;

  connect(startBtn, &QPushButton::clicked, this,
          &SlotMachineController::startGame);
  connect(stopBtn, &QPushButton::clicked, this,
          &SlotMachineController::stopGame);

  return true;
}

bool SlotMachineController::createConnectWithTimer(
    const int &msec, void (SlotMachineController::*func)()) {
  bool code = false;
  try {
    QTimer *t = new QTimer(this);
    t->setInterval(msec);

    connect(t, &QTimer::timeout, this, func);
    t->start();
    code = true;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  } catch (...) {
    std::cerr << "Unknown exception\n";
  }

  return code;
}

SlotMachineController::SlotMachineController(SlotMachine *model,
                                             SlotMachineView *view)
    : _model(model), _view(view) {
  if (_view == nullptr || _model == nullptr) {
    QMessageBox::critical(nullptr, "Error", "View or Model is null");
    QCoreApplication::exit(1);
    return;
  }

  if (_view->isGoodData() == false) {
    QMessageBox::critical(nullptr, "Error", "View problem");
    QCoreApplication::exit(1);
    return;
  }

  if (!connectToBtn()) {
    QMessageBox::critical(nullptr, "Error", "Error connect to button.");
    QCoreApplication::exit(1);
    return;
  }

  if (!createConnectWithTimer(10, &SlotMachineController::UpdateView)) {
    QMessageBox::critical(nullptr, "Error", "Error update view.");
    QCoreApplication::exit(1);
    return;
  }

  if (!createConnectWithTimer(10,
                              &SlotMachineController::ProcessingUserInput)) {
    QMessageBox::critical(nullptr, "Error", "Error processing user input.");
    QCoreApplication::exit(1);
    return;
  }

  _view->show();
}

SlotMachineController::~SlotMachineController() {}

void SlotMachineController::startGame() { _action = Action::Start; }
void SlotMachineController::stopGame() { _action = Action::Stop; }

void SlotMachineController::ProcessingUserInput() {
  if (_model) {
    _model->UserInput(_action);
    _action = Action::NoAction;
  }
}

void SlotMachineController::UpdateView() {
  if (_view && _view->isGoodData())
    _view->updateView(_model->getGameInfoForUpdateView());
}
