#include "misc.hpp"
#include <GL/gl.h>
#include "sfe_demo.hpp"
#include "timeline.hpp"
#include "display_gl.hpp"

SFE_Demo::SFE_Demo(int argc, char** argv) : Program(argc, argv) {
	// SET PROGRAM ATTRIBUTES:
		name = "SFE Demo";
		version = "0.0002";
}

SFE_Demo::~SFE_Demo() {
}

bool SFE_Demo::init() {
	// INITIALIZE TIMELINE:
		timeline = new Timeline();
		timeline->init();
	// SET UP DISPLAY DEVICE:
		display = new Display_GL();
		display->set_width(800);
		display->set_height(600);
		display->set_desiredfps(50);
		display->setup();

		//display->resizable_window = false;
		//display->vsync = true;
		//display->mousecursor_visible = false;
		display->set_fullscreen(false);

	//Program::init();
	return this->works;
}

bool SFE_Demo::world_room_init() {
	Trianglelist* polygon_a = new Trianglelist();
	Trianglelist* polygon_b = new Trianglelist();
	return true;	// TODO
}

bool SFE_Demo::mainloop() {
	while (!mainloop_done and this->works) {
		uint32_t time_elapsed = timeline->get_position();
		//world_room.camera.rotate(timeline.get_position(), 0, 0);
		get_events();
		if (keyboard->buttonstates[SDL_SCANCODE_KP_PLUS])
			timeline->set_position(timeline->position + 1000);

		if (keyboard->buttonstates[SDL_SCANCODE_KP_MINUS])
			timeline->set_position(timeline->position - 1000);

		if (keyboard->buttonstates[SDL_SCANCODE_PAGEUP])
			timeline->set_position(timeline->position + 10000);

		if (keyboard->buttonstates[SDL_SCANCODE_PAGEDOWN])
			timeline->set_position(timeline->position - 10000);

		if (keyboard->buttonstates[SDL_SCANCODE_KP_MULTIPLY])
			timeline->set_speed(timeline->speed * 1.1);

		if (keyboard->buttonstates[SDL_SCANCODE_KP_DIVIDE])
			timeline->set_speed(timeline->speed * 0.9);

		if (keyboard->get_presscount(SDL_SCANCODE_HOME))
			timeline->set_position(0);

		//if (keyboard->get_presscount(SDL_SCANCODE_END))
			//timeline->set_position();

		glBegin(GL_QUADS);				// Each set of 4 vertices form a quad
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.5f, -0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.5f,  0.5f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(-0.5f,  0.5f);
		glEnd();

		display->refresh();

	}
	return this->works;
}
