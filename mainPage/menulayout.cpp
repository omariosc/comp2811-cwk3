#include "menulayout.h"

MenuLayout::MenuLayout() : QGridLayout() {
    setColumnStretch(0, 1);
    setColumnStretch(1, 1);
    setColumnStretch(2, 1);
    setColumnStretch(3, 1);
    setMargin(0);
    setSpacing(0);
}
