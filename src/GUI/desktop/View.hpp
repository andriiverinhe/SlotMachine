#pragma once

#include <QWidget>

#include "../../backend/SlotMachineInfo.hpp"

class QPushButton;
class QLabel;
class QPainter;
class QPaintEvent;
class QVBoxLayout;
class QResizeEvent;

class SlotMachineView : public QWidget {
  Q_OBJECT

 public:
  SlotMachineView(QWidget *parent = nullptr);
  ~SlotMachineView();

  void updateView(const SlotMachineInfo &info);
  bool isGoodData(void) const;

  const QPushButton *getStartButton(void) const;
  const QPushButton *getStopButton(void) const;

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  bool isGood = false;

  static constexpr int COUNT_DRUMS = 5;
  static constexpr int COUNT_FIGURE_FOR_DRUM = 3;

  unsigned margin = 100;
  SlotMachineInfo _info;

  QPushButton *_startBtn;
  QPushButton *_stopBtn;
  QLabel *_resultLabel;

  QVBoxLayout *_menuLayout;

  bool createBtn();
  bool createResultLabel();

  void DrawFigure(const FigureType &, int x, int y, int width, int height);
  void drawStar(QPainter &painter, int x, int y, int width, int height);
  void drawTriangle(QPainter &painter, int x1, int y1, int x2, int y2, int x3,
                    int y3);
  void drawTriangle(QPainter &painter, int x, int y, int width, int height);
  void drawSquare(QPainter &painter, int x, int y, int width, int height);
  void drawCircle(QPainter &painter, int x, int y, int width, int height);

  void updateResult(const QString &result);
  void resizeEvent(QResizeEvent *event);
};
