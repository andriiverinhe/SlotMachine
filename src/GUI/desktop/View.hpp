#pragma once

#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QWidget>

#include "../../backend/SlotMachine.hpp"

class SlotMachineView : public QWidget {
  Q_OBJECT

 private:
  GameInfo gameInfo;

 public:
  SlotMachineView(QWidget *parent = nullptr);
  ~SlotMachineView();

  void updateView(const GameInfo &gameInfo);

 protected:
  void paintEvent(QPaintEvent *event) override;

 public:
  QPushButton *startButton_;
  QPushButton *stopButton_;
  QHBoxLayout *layout_;
  QVBoxLayout *buttonLayout;

  void drawStar(int x, int y, int size);
  void drawTriangle(int x, int y, int size);
  void drawSquare(int x, int y, int size);
  void drawCircle(int x, int y, int size);

  void resizeEvent(QResizeEvent *event);
};