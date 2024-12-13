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
  // setMinimumSize(1800, 920);
}

SlotMachineView::~SlotMachineView() {}

void SlotMachineView::updateView(const GameInfo &gameInfo) {
  this->gameInfo = gameInfo;
  repaint();
}

int scaleValue(int x, int A, int B) {
    return (x / A) * B;
}

void SlotMachineView::paintEvent(QPaintEvent *event) {
  const GameInfo gi = gameInfo; 

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  int margin = 100;
  int availableWidth = width() - 2 * margin;
  int availableHeight = height() - 2 * margin;

  int fieldWidth = availableWidth * 0.75;
  int fieldHeight = availableHeight;

  int x = margin;
  int y = margin;

  painter.setClipRect(x, y, fieldWidth, fieldHeight);

  painter.setPen(Qt::red);
  painter.drawRect(x, y, fieldWidth, fieldHeight);

  for (int i = 0; i < gi._data.size(); i++) {
    int figureX = x + i * (fieldWidth / 5);
    painter.drawLine(figureX, y, figureX, y + fieldHeight);
  }

  for (int i = 0; i < gi._data.size(); i++) {
    for (int j = 0; j < gi._data[i].size(); j++) {
      int size = std::min(fieldWidth / 5, fieldHeight / 3);
      
      int figureX = x + i * (fieldWidth / 5);

      int figureY = y + (scaleValue(gi._data[i][j].getPosition().y, 30, size));

      int figure = 0;
      int test = 0;

      try {
        if (!gi._data.empty())
          if (!gi._data[i].empty()) test = (int)gi._data[i][j].getType();

      } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Error:", e.what());
        test = 0;
      }

      switch (test) {
        case 0:
        default:
          drawCircle(figureX, figureY, size);
          break;
        case 1:
          drawTriangle(figureX, figureY, size);
          break;
        case 2:
          drawSquare(figureX, figureY, size);
          break;
        case 3:
          drawStar(figureX, figureY, size);
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

  int margin = 100;
  int availableWidth = width() - 2 * margin;
  int availableHeight = height() - 2 * margin;

  int fieldWidth = availableWidth * 0.75;
  int fieldHeight = availableHeight;

  int _x = margin;
  int _y = margin;

  QPainter painter(this);
  painter.setClipRect(_x, _y, fieldWidth, fieldHeight);
  painter.drawPath(path);
}

void SlotMachineView::drawTriangle(int x, int y, int size) {
  QPainterPath path;
  path.moveTo(x + size / 2, y);
  path.lineTo(x, y + size);
  path.lineTo(x + size, y + size);
  path.closeSubpath();

  int margin = 100;
  int availableWidth = width() - 2 * margin;
  int availableHeight = height() - 2 * margin;

  int fieldWidth = availableWidth * 0.75;
  int fieldHeight = availableHeight;

  int _x = margin;
  int _y = margin;

  QPainter painter(this);
  painter.setClipRect(_x, _y, fieldWidth, fieldHeight);

  painter.drawPath(path);
}

void SlotMachineView::drawSquare(int x, int y, int size) {
  int margin = 100;
  int availableWidth = width() - 2 * margin;
  int availableHeight = height() - 2 * margin;

  int fieldWidth = availableWidth * 0.75;
  int fieldHeight = availableHeight;

  int _x = margin;
  int _y = margin;

  QPainter painter(this);
  painter.setClipRect(_x, _y, fieldWidth, fieldHeight);
  painter.drawRect(x, y, size, size);
}

void SlotMachineView::drawCircle(int x, int y, int size) {
  int margin = 100;
  int availableWidth = width() - 2 * margin;
  int availableHeight = height() - 2 * margin;

  int fieldWidth = availableWidth * 0.75;
  int fieldHeight = availableHeight;

  int _x = margin;
  int _y = margin;

  QPainter painter(this);
  painter.setClipRect(_x, _y, fieldWidth, fieldHeight);
  painter.drawEllipse(x, y, size, size);
}

void SlotMachineView::resizeEvent(QResizeEvent *event) {
  int width = event->size().width();
  int leftMargin = width * 0.7;
  if (buttonLayout) buttonLayout->setContentsMargins(leftMargin, 10, 10, 10);
  QWidget::resizeEvent(event);
}
