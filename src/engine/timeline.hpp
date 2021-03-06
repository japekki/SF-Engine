/*
	SF-Engine

	This file has routines for the timeline.
*/

// There are three kind of things to put into timeline:
// - Things that are calculated in this frame only. Sprite drawing for example.
// - Things that need to be calculated cumulative so that the previous results are needed in further calculations.
// - Nested sub-timelines

#ifndef TIMELINE_HPP
	#define TIMELINE_HPP

	#include <vector>

	// SYNC TYPES:
		#define SYNC_NONE 0
		#define SYNC_CLOCK 1

	// ACTION TYPES:
		#define TIMELINE_JUMPTO		1
		#define TIMELINE_CALLBACK	2
		//#define TIMELINE_KEYFRAME	3

	class Action {
		public:
			int occuretime;
			unsigned char type;
			bool cumulative;
			void *function;	// If type is callback
			int jumpto;		// If type is jumpto
	};

	class Timeline {
		public:
			int init_timestamp = 0;		// Program will start from index 0 at the timeline, when synced to clock
			int position = 0;			// current running position in milliseconds
			int previous_position = 0;	// when we last polled an action
			uint32_t duration = 0;		// milliseconds
			float speed = 1;			// + or -, 1 = "normal speed", negative plays backwards
			bool running = false;
			std::vector<Action> actions;
			Timeline();
			~Timeline();
			void init();
			//void sync(unsigned char sync_type);
			int get_position();
			void set_position(int position);
			void jump_forwards(int time);
			void jump_backwards(int time);
			void set_speed(float new_speed);
			//void add_action(int time, void *function);
			void clear();			// clear all actions
			void start();
			void stop();			// Pause
			int time_until_next_action();
			std::vector<Action> get_actions_between(int time_from, int time_to);
	};

#endif // TIMELINE_HPP
