#include "gui.hpp"

void Scrollbar::scroll_to(uint32_t x, uint32_t y) {
}

void Menu::add_menuentry(Menuentry* menuentry) {
	menuentries.push_back(menuentry);
}

void Widgetarea::add_widget(Widget* widget) {
	widgets.push_back(widget);
}

Widget* Widgetarea::clicked() {
	return nullptr;	// TODO
}
