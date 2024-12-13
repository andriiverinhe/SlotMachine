#include "View.hpp"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QResizeEvent>
#include <QString>
#include <QVBoxLayout>
#include <iostream>

SlotMachineView::SlotMachineView(QWidget *parent) : QWidget(parent) {
  startButton_ = new QPushButton("Start", this);
  stopButton_ = new QPushButton("Stop", this);

  startButton_->setFixedSize(300, 50);
  stopButton_->setFixedSize(300, 50);

  buttonLayout = new QVBoxLayout();
  buttonLayout->addWidget(startButton_);
  buttonLayout->addWidget(stopButton_);

  buttonLayout->setContentsMargins(20, 0, 0, 0);

  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(this);
  mainLayout->addLayout(buttonLayout);

  mainLayout->setContentsMargins(100, 100, 100, 250);
  setLayout(mainLayout);
  setMinimumSize(1800, 600);
}

SlotMachineView::~SlotMachineView() {}

void SlotMachineView::updateView(const GameInfo &gameInfo) {
  this->gameInfo = gameInfo;
  repaint();
}

void SlotMachineView::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  int margin = 100;
  int availableWidth = width() - 2 * margin;
  int availableHeight = height() - 2 * margin;

  int fieldWidth = availableWidth * 0.75;
  int fieldHeight = availableHeight;

  int x = margin;
  int y = margin;

  painter.drawRect(x, y, fieldWidth, fieldHeight);

  for (int i = 0; i < 5; i++) {
    int figureX = x + i * (fieldWidth / 5);
    painter.drawLine(figureX, y, figureX, y + fieldHeight);
  }

  for (int i = 0; i < 3; i++) {
    int figureY = y + i * (fieldHeight / 3);
    painter.drawLine(x, figureY, x + fieldWidth, figureY);
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      int figure = 1;
      int figureX = x + i * (fieldWidth / 5);
      int figureY = y + j * (fieldHeight / 3);

      int size = std::min(fieldWidth / 5, fieldHeight / 3);

      switch (figure) {
        case 0:
          drawStar(figureX, figureY, size);
          break;
        case 1:
          painter.drawEllipse(figureX, figureY, size, size);
          break;
        case 2:
          painter.drawRect(figureX, figureY, size, size);
          break;
        case 3:
          drawTriangle(figureX, figureY, size);
          break;
      }
    }
  }
}

void SlotMachineView::drawStar(int x, int y, int size) {
  QPainterPath path;
  path.moveTo(x + size / 2, y);
  path.lineTo(x + size / 4, y + size / 2);
  path.lineTo(x + size / 2, y + size);
  path.lineTo(x + size * 3 / 4, y + size / 2);
  path.lineTo(x + size / 2, y);
  QPainter painter(this);
  painter.drawPath(path);
}

void SlotMachineView::drawTriangle(int x, int y, int size) {
  QPainterPath path;
  path.moveTo(x + size / 2, y);
  path.lineTo(x, y + size);
  path.lineTo(x + size, y + size);
  path.closeSubpath(); 
  QPainter painter(this);
  painter.drawPath(path);
}

void SlotMachineView::resizeEvent(QResizeEvent *event) {
  int width = event->size().width();
  int leftMargin = width * 0.7;
  buttonLayout->setContentsMargins(leftMargin, 10, 10, 10);
  QWidget::resizeEvent(event);
}