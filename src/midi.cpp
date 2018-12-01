#include "midi.hpp"

/*
#ifdef LINUX
	#include <sys/soundcard.h>
	void init() {
	}
	void test() {
			unsigned char inpacket[4];
			// first open the sequencer device for reading:
			int seqfd = open(MIDI_DEVICE, O_RDONLY);
			if (seqfd == -1) {
				CERR << "MIDI: Error opening device " << MIDI_DEVICE << endl;
				exit(1);
			}
			// now just wait around for MIDI bytes to arrive and print them to screen.
			while (1)
			{
				read(seqfd, &inpacket, sizeof(inpacket));
				//#ifdef WITH_DEBUGMSG
					// print the MIDI byte if this input packet contains one
					if (inpacket[0] == SEQ_MIDIPUTC) {
						printf("MIDI: received byte: %d\n", inpacket[1]);
					}
				//#endif
			}
	}

#elseifdef WIN32

	void init() {
	}

	void test() {	// some example code ripped from the Internet
	//
	//	#include <stdio.h>     // for printf() function

	//	#include <windows.h>   // required before including mmsystem.h
	//	#include <mmsystem.h>  // multimedia functions (such as MIDI) for Windows

	//	int ckey;           // storage for the current keyboard key being pressed
	//	int velocity = 100; // MIDI note velocity parameter value
	//	int midiport;       // select which MIDI output port to open
	//	int flag;           // monitor the status of returning functions
	//	HMIDIOUT device;    // MIDI device interface for sending MIDI output

	//	// variable which is both an integer and an array of characters:
	//	union { unsigned long word; unsigned char data[4]; } message;
	//	// message.data[0] = command byte of the MIDI message, for example: 0x90
	//	// message.data[1] = first data byte of the MIDI message, for example: 60
	//	// message.data[2] = second data byte of the MIDI message, for example 100
	//	// message.data[3] = not used for any MIDI messages, so set to 0
	//	message.data[0] = 0x90;  // MIDI note-on message (requires to data bytes)
	//	message.data[1] = 60;    // MIDI note-on message: Key number (60 = middle C)
	//	message.data[2] = 100;   // MIDI note-on message: Key velocity (100 = loud)
	//	message.data[3] = 0;     // Unused parameter

	//	// Assign the MIDI output port number (from input or default to 0)
	//	if (argc < 2) {
	//		midiport = 0;
	//	} else {
	//		midiport = atoi(argv[1]);
	//	}
	//	printf("MIDI output port set to %d.\n", midiport);

	//	// Open the MIDI output port
	//	flag = midiOutOpen(&device, midiport, 0, 0, CALLBACK_NULL);
	//	if (flag != MMSYSERR_NOERROR) {
	//		printf("Error opening MIDI Output.\n");
	//		return 1;
	//	}

	//	if (notestate == 0) {
	//		// Note is currently off, turn on note.
	//		message.data[2] = velocity;
	//	} else {
	//		// Note is currently on, turn off note.
	//		message.data[2] = 0;  // 0 velocity = note off
	//	}
	//		flag = midiOutShortMsg(device, message.word);
	//		if (flag != MMSYSERR_NOERROR) {
	//		printf("Warning: MIDI Output is not open.\n");
	//	}
	//	if (ckey == 'q') break;

		// turn any MIDI notes currently playing:
	//	midiOutReset(device);
	//}
	}

	void midi_free() {
		// Remove any data in MIDI device and close the MIDI Output port:
		//midiOutClose(device);
	}

#endif
*/
