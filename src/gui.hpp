/*
	SF-Engine

	This file has routines for graphical user interface (dialogs, widgets etc.)
*/

/*
TODO:
- Startup dialog / launcher
- Threaded dialogs for changing or watching parameters
- Auto resize to prevent overlapping with small resolution or extreme aspect ratio
*/

#ifndef GUI_HPP
	#define GUI_HPP

	#include <SDL.h>
	#include <string>
	#include <vector>

	class Widget {
		public:
			SDL_Rect rect;
	};

	class Input_text : public Widget {
		public:
			std::string text;
	};

	class Button : public Widget {
		public:
			std::string text;
	};

	class Radiobutton : public Widget {
	};

	class Radiogroup : public Widget {
	};

	class Scrollbar : public Widget {
		public:
			unsigned int scrollposition_x;
			unsigned int scrollposition_y;
			void scroll_to(unsigned int x, unsigned int y);
	};

	class Menuentry : public Widget {
	};

	class Menu : public Widget {
		public:
			std::vector<Menuentry*> menuentries;
			void add_menuentry(Menuentry* menuentry);
	};

	class Tab : public Widget {
	};

	class Tabgroup : public Widget {
		public:
			std::vector<Tab*> tabs;
			void add_tab(Tab* tab);
	};

	class Window : public Widget {
		public:
			std::string title;
	};

	class Widgetarea {
		public:
			std::vector<Widget*> widgets;
			void add_widget(Widget* widget);
			Widget* clicked();	// Which widget was clicked
	};

#endif // GUI_HPP
