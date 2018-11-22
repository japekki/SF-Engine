# SF-Engine
Multiplatform Demo / game engine.

Version: 0.001

Features:

Multiplatform, 2D and 3D CPU rendering, tracker music, MIDI, joystick etc.

Currently only CPU rendering is supported, athough SDL2 may give some sort of DirectX and OpenGL/GLES acceleration even on 2D.

Includes a few sample programs that are supposed to be separate projects some day: CaveBombers, Foobar (demo), Pinball, RocketZ, PubLiippari (screensaver), Tetrex

The music in RocketZ sample program is [a remix made by Nuggumath](https://www.youtube.com/watch?v=o3TkUdJ8NlA) of one of the original Wings game music tunes called [PELIMUSA.S3M, made by Jussi Huhtala)](https://www.youtube.com/watch?v=XKs5mkEpWuU).

I have a permission from Nuggumath to use his remix, but I decided not to include the original here in git since I have not asked for permission, and I'm probably not going to use it anyway since it already has been used in Wings.

But I've been using that tune while programming this, just to get into the mood. :) So you'll get an error message of that file missing, just ignore it.

Currently supported/tested operating systems and compilers:

MS-Windows (MinGW), GNU/Linux, GNU g++

Should compile to both 32 and 64 bit executable.

Depencies: SDL2, SDL2_mixer, SDL2_image

NOTE: 32 bit version, at least on MinGW, gives an error when trying to load a .PNG file. It says something about inflateValidate procedure, not sure why this is, probably a bug in some version of SDL2_image / libpng16-16.dll / zlib1.dll I guess...

![screenshot](http://titanix.net/~japek/archive/RocketZ_0.0001.png)
