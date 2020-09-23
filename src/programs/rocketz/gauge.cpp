#include "gauge.hpp"
#include "gameplay.hpp"

Gauge::Gauge(Gameplay* gameplay) {
	this->gameplay = gameplay;
}

void Gauge::draw(int x, int y) {
	// Draw line from A to B
	//int distance = this->width / this->maximum * this->value;
	//gameplay->display->draw_line(Point(0, 0), Point(100,100), 80, 80, 80);
}
