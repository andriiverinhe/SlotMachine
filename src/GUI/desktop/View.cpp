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

bool SlotMachineView::isGoodData(void) const { return isGood; }

bool SlotMachineView::createBtn() {
  bool code = false;

  try {
    _startBtn = new QPushButton("Start", this);
    _stopBtn = new QPushButton("Stop", this);

    if (_startBtn == nullptr || _stopBtn == nullptr) return false;

    _startBtn->setFixedHeight(50);
    _stopBtn->setFixedHeight(50);

    code = true;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
  } catch (...) {
    std::cerr << "Unknown error occurred.\n";
  }
  return code;
}

bool SlotMachineView::createResultLabel() {
  if (_menuLayout == nullptr) return false;

  bool code = false;

  try {
    QFrame *_resultFrame = new QFrame(this);
    if (_resultFrame == nullptr) return false;

    _resultFrame->setFrameShape(QFrame::StyledPanel);
    _resultFrame->setFrameShadow(QFrame::Raised);
    _resultFrame->setLineWidth(2);

    _resultLabel = new QLabel("Winning: 0", this);
    if (_resultLabel == nullptr) return false;

    QFont font("Arial", 16, QFont::Bold);
    _resultLabel->setFont(font);

    _resultLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *resultLayout = new QVBoxLayout(_resultFrame);

    if (resultLayout == nullptr) return false;
    resultLayout->addWidget(_resultLabel);
    resultLayout->setContentsMargins(10, 10, 10, 10);

    if (_menuLayout == nullptr) return false;
    _menuLayout->addWidget(_resultFrame);
    code = true;

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  } catch (...) {
    std::cerr << "Unknown error occurred.\n";
  }
  return code;
}

SlotMachineView::SlotMachineView(QWidget *parent) : QWidget(parent) {
  if (!createBtn()) return;

  _menuLayout = new QVBoxLayout();

  _menuLayout->addWidget(_startBtn);
  _menuLayout->addWidget(_stopBtn);

  if (!createResultLabel()) return;

  try {
    QSpacerItem *spacer =
        new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    if (spacer == nullptr) return;

    _menuLayout->addItem(spacer);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    if (mainLayout == nullptr) return;

    mainLayout->addLayout(_menuLayout);
    mainLayout->setContentsMargins(margin, margin, margin, margin);

    setLayout(mainLayout);
    isGood = true;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  } catch (...) {
    std::cerr << "Unknown error occurred.\n";
  }
}

SlotMachineView::~SlotMachineView() {}

void SlotMachineView::updateView(const GameInfo &gameInfo) {
  if (isGood) {
    this->gameInfo = gameInfo;
    repaint();
  }
}

const QPushButton *SlotMachineView::getStartButton(void) const {
  return _startBtn;
}
const QPushButton *SlotMachineView::getStopButton(void) const {
  return _stopBtn;
}

void SlotMachineView::updateResult(const QString &result) {
  if (isGood) _resultLabel->setText("Winning: " + result);
}

void SlotMachineView::paintEvent(QPaintEvent *event) {
  if (!isGood) return;

  const GameInfo gi = gameInfo;

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  int fieldWidth = gi.sizeOneFigure.width * COUNT_DRUMS;
  int fieldHeight = gi.sizeOneFigure.height * COUNT_FIGURE_FOR_DRUM;

  painter.setPen(Qt::black);
  painter.drawRect(margin, margin, fieldWidth, fieldHeight);

  for (int i = 0; i < gi.data.size(); i++) {
    const int figureX = margin + i * (fieldWidth / COUNT_DRUMS);
    for (int j = 0; j < gi.data[i].size(); j++) {
      const int figureY = margin + gi.data[i][j].getLocation().y;

      if (!gi.data.empty())
        if (!gi.data[i].empty()) {
          DrawFigure(gi.data[i][j].getType(), figureX, figureY,
                     gi.sizeOneFigure.width, gi.sizeOneFigure.height);
          updateResult(QString::number(gi.point));
        }
    }
  }
}

void SlotMachineView::DrawFigure(const FigureType &type, int x, int y,
                                 int width, int height) {
  const int fieldWidth = gameInfo.sizeOneFigure.width * COUNT_DRUMS;
  const int fieldHeight =
      gameInfo.sizeOneFigure.height * COUNT_FIGURE_FOR_DRUM;

  QPainter painter(this);
  painter.setClipRect(margin, margin, fieldWidth + 1, fieldHeight + 1);
  painter.drawRect(x, y, width, height);

  switch (type) {
    case FigureType::circle:
      drawCircle(painter, x, y, width, height);
      break;
    case FigureType::triangle:
      drawTriangle(painter, x, y, width, height);
      break;
    case FigureType::square:
      drawSquare(painter, x, y, width, height);
      break;
    case FigureType::star:
      drawStar(painter, x, y, width, height);
      break;

    default:
      break;
  }
}

void SlotMachineView::drawStar(QPainter &painter, int x, int y, int width,
                               int height) {
  const int padding = 30;
  const int padding2 = padding * 2;

  const int startX = x + padding;
  const int startY = y + padding;

  const int offset_x1 = (width - padding2);
  const int offset_x2 = offset_x1 / 2;

  const int offset_y1 = height - padding2;
  const int offset_y2 = offset_y1 - offset_y1 / 3.5;
  const int offset_y3 = offset_y1 / 2.6;

  const int x1 = startX + offset_x2;  // top
  const int y1 = startY;              // top

  const int x2 = x1;              // bottom
  const int y2 = y1 + offset_y2;  // bottom

  const int x3 = startX;          // left mid
  const int y3 = y1 + offset_y3;  // left mid

  const int x4 = startX + offset_x1;  // right mid
  const int y4 = y3;                  // right mid

  const int x5 = x1 - offset_x2;  // left bottom
  const int y5 = y1 + offset_y1;  // left bottom

  const int x6 = x1 + offset_x2;  // right bottom
  const int y6 = y5;              // right bottom

  drawTriangle(painter, x1, y1, x5, y5, x2, y2);
  drawTriangle(painter, x1, y1, x6, y6, x2, y2);
  drawTriangle(painter, x3, y3, x4, y4, x2, y2);
}

void SlotMachineView::drawTriangle(QPainter &painter, int x1, int y1, int x2,
                                   int y2, int x3, int y3) {
  QPainterPath path;
  path.moveTo(x1, y1);
  path.lineTo(x2, y2);
  path.lineTo(x3, y3);
  path.closeSubpath();

  painter.setBrush(Qt::black);
  painter.drawPath(path);
}

void SlotMachineView::drawTriangle(QPainter &painter, int x, int y, int width,
                                   int height) {
  const int padding = 30;
  const int padding2 = padding * 2;

  const int x1 = x + padding + (width - padding2) / 2;
  const int y1 = y + padding;

  const int x2 = x + padding;
  const int y2 = y + padding + (height - padding2);

  const int x3 = x + padding + (width - padding2);
  const int y3 = y + padding + (height - padding2);

  drawTriangle(painter, x1, y1, x2, y2, x3, y3);
}

void SlotMachineView::drawSquare(QPainter &painter, int x, int y, int width,
                                 int height) {
  painter.setBrush(Qt::black);
  const int padding = 30;
  const int padding2 = padding * 2;
  painter.drawRect(x + padding, y + padding, width - padding2,
                   height - padding2);
}

void SlotMachineView::drawCircle(QPainter &painter, int x, int y, int width,
                                 int height) {
  painter.setBrush(Qt::black);
  const int padding = 30;
  const int padding2 = padding * 2;
  painter.drawEllipse(x + padding, y + padding, width - padding2,
                      height - padding2);
}

void SlotMachineView::resizeEvent(QResizeEvent *event) {
  int leftMargin = margin + gameInfo.sizeOneFigure.width * COUNT_DRUMS;
  if (_menuLayout) _menuLayout->setContentsMargins(leftMargin, 10, 10, 10);
  QWidget::resizeEvent(event);
}
