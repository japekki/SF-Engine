#ifndef MIDI_HPP
	#define MIDI_HPP

//namespace midi {

	void init();
	void test();

	#ifdef LINUX
		#define MIDI_DEVICE "/dev/sequencer"
	#endif

//}

#endif // MIDI_HPP
