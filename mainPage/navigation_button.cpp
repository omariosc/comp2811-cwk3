#include "navigation_button.h"

#include <QDebug>
#include <QStyle>
#include <QVariant>

NavigationButton::NavigationButton(QString newName)
    : QToolButton(), name(newName) {
  setActive(false);
  setText(newName);
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  QSizePolicy buttonPolicy = QSizePolicy();
  buttonPolicy.setWidthForHeight(1);
  buttonPolicy.setHorizontalPolicy(QSizePolicy::Ignored);
  buttonPolicy.setVerticalPolicy(QSizePolicy::Minimum);
  setSizePolicy(buttonPolicy);

  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  setIconSize(QSize(48, 48));

  connect(this, &NavigationButton::released, this,
          &NavigationButton::dataClicked);
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
  // Refresh style sheet as type property is changed
  this->style()->unpolish(this);
  this->style()->polish(this);
}
