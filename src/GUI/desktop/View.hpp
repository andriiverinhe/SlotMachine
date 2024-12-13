#pragma once

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QHBoxLayout>
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
  void resizeEvent(QResizeEvent *event);
};