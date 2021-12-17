#include "navigation_button.h"
#include <QDebug>
#include <QStyle>
#include <QVariant>

NavigationButton::NavigationButton(QString newName) : QToolButton() {
  setActive(false);
  setName(newName);
  setText(newName);
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  QSizePolicy myPolicy = QSizePolicy();
  myPolicy.setWidthForHeight(1);
  myPolicy.setHorizontalPolicy(QSizePolicy::Ignored);
  myPolicy.setVerticalPolicy(QSizePolicy::Minimum);
  setSizePolicy(myPolicy);
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  setIconSize(QSize(48, 48));
  connect(this, SIGNAL(clicked()), this, SLOT(dataClicked()));
}

void NavigationButton::setName(QString newName) { this->name = newName; }

void NavigationButton::setPageNum(int pageNum) { this->pageNum = pageNum; }

void NavigationButton::dataClicked() { emit clicked(pageNum, name); }

void NavigationButton::setActive(bool newState) {
  if (newState) {
    setProperty("type", "Selected");
  } else {
    setProperty("type", "Unselected");
  }
  this->style()->unpolish(this);
  this->style()->polish(this);
}
