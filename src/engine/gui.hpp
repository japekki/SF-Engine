/*
	SF-Engine

	This file has routines for graphical user interface (dialogs, widgets etc.)
*/

/*
TODO:
- Auto resize to prevent overlapping with small resolution or extreme aspect ratio
*/

#ifndef GUI_HPP
	#define GUI_HPP

	#include <SDL.h>
	#include <string>
	#include <vector>

	class Widget {
		public:
			//Point location;
			SDL_Rect rect;
			bool draw();
	};

	class Input_text : public Widget {
		public:
			std::string text;
	};

	class Button : public Widget {
		public:
			std::string text;
	};

	class Checkbox : public Widget {
		bool value;	// or 'checked'?
	};

	class Radiobutton : public Widget {
	};

	class Radiogroup : public Widget {
	};

	class Scrollbar : public Widget {
		public:
			uint32_t scrollposition_x;
			uint32_t scrollposition_y;
			void scroll_to(uint32_t x, uint32_t y);
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
