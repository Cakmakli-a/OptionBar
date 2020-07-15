#ifndef OPTIONBAR_HPP
#define OPTIONBAR_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QAction>
#include <QPaintEvent>
#include <QPainter>
#include <QRectF>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QDebug>

class OptionBar : public QWidget
{

  Q_OBJECT

public:
  explicit OptionBar(QWidget *parent = nullptr);
  virtual ~OptionBar();

  QSize minimumSizeHint() const override;
  void addAction(QAction* action);

private:
  QHBoxLayout* hLayout;
  QFrame* frame;
  QPropertyAnimation* animation;
  QList<QAction*> actionList;
  QList<QPushButton*> buttons;
  QPushButton* selectedButton;

  const int adjustedParent = 2;
  const int adjustedLabel = 4;
  const int roundedRectParent = 6;
  const float offsetX = 4.0f;
  const int minimumHeight = 34;

public slots:
  void mouseRelease();

protected:
  void paintEvent(QPaintEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

signals:
  void actionSelected(QAction* action);

};

#endif // OPTIONBAR_HPP
