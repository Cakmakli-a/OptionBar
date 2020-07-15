#include "optionbar.hpp"

OptionBar::OptionBar(QWidget *parent) : QWidget(parent)
{
  setMouseTracking(true);
  this->frame = new QFrame();
  this->frame->setParent(this);
  this->frame->setStyleSheet("QFrame { background: qlineargradient(x0:0, y0:0, x0:0, y1:1, \
    stop:0 #FEFEFE, stop:1 #FFFFFF); border-radius: 4px; }");

  this->hLayout = new QHBoxLayout(this);
  this->hLayout->setMargin(0);
  this->hLayout->setSpacing(0);

  this->animation = new QPropertyAnimation(this->frame, "pos", this);
  this->animation->setDuration(800);
  this->animation->setEasingCurve(QEasingCurve::OutExpo);

  this->setLayout(this->hLayout);

  QObject::connect(this->animation, &QPropertyAnimation::finished, [&]() {
    QAction* action = this->selectedButton->actions().first();
    emit actionSelected(action);
  });
}

OptionBar::~OptionBar()
{
  delete this->animation;
  delete this->frame;
  delete this->hLayout;
}

void OptionBar::addAction(QAction* action)
{
  QPushButton* pushButton = new QPushButton(action->text(), this);
  if (this->actionList.isEmpty()) {
    this->selectedButton = pushButton;
  }
  if (action->isChecked()) {
    this->actionList.push_back(action);
  }
  this->actionList.push_back(action);
  pushButton->setAutoFillBackground(false);
  pushButton->addAction(action);
  pushButton->setFlat(true);
  pushButton->setStyleSheet("QPushButton { background-color: transparent; color: #383838; } \
    QPushButton:pressed { background-color: transparent; }");
  pushButton->setCheckable(false);
  pushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->buttons.push_back(pushButton);
  this->hLayout->addWidget(pushButton);
  QObject::connect(pushButton, &QPushButton::clicked, this, &OptionBar::mouseRelease);
}

void OptionBar::mouseRelease()
{
  if (this->animation->state() == QPropertyAnimation::State::Running) {
      return;
  }
  QObject* object = sender();
  if (qobject_cast<QPushButton*>(object)) {
    QPushButton* button = qobject_cast<QPushButton*>(object);
    this->animation->setStartValue(QPointF(this->frame->x(), this->frame->y()));
    this->animation->setEndValue(QPointF(button->x() + this->offsetX, this->frame->y()));
    this->selectedButton = button;
    this->animation->start();
  }
}

void OptionBar::paintEvent(QPaintEvent* event)
{
  QPainter p(this);
  p.save();
  p.setRenderHint(QPainter::Antialiasing);
  QRectF rectF(rect().adjusted(+this->adjustedParent, +this->adjustedParent, -this->adjustedParent, -this->adjustedParent));
  QPainterPath path;
  path.addRoundedRect(rectF, this->roundedRectParent, this->roundedRectParent);
  p.fillPath(path, QColor::fromRgb(196, 196, 196));
  p.restore();
  this->QWidget::paintEvent(event);
}


void OptionBar::resizeEvent(QResizeEvent* event)
{
  Q_UNUSED(event)
  if (this->selectedButton) {
    const QRect rect = this->selectedButton->rect();
    this->frame->setGeometry(rect.adjusted(+this->adjustedLabel, +this->adjustedLabel, -this->adjustedLabel, -this->adjustedLabel));
    this->frame->updateGeometry();
  }
  this->QWidget::resizeEvent(event);
}


QSize OptionBar::minimumSizeHint() const
{
  return QSize(minimumWidth(), this->minimumHeight);
}
