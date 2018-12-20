#include "gui.hpp"

void Scrollbar::scroll_to(unsigned int x, unsigned int y) {
}

void Menu::add_menuentry(Menuentry* menuentry) {
	this->menuentries.push_back(menuentry);
}

void Widgetarea::add_widget(Widget* widget) {
	this->widgets.push_back(widget);
}

Widget* Widgetarea::clicked() {
}
