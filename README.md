# SF-Engine
## Demo / game engine.

## Versions

### Engine:

SFE: 0.0004

SFE Benchmark: 0.0001

SFE Demo: 0.0001

### Sample programs:

CaveBombers: 0.0002

Pinball: 0.0002

RocketZ: 0.0005

Pub Liippari: 0.0002

Tetrex: 0.0002

## Features

Multiplatform, 2D and 3D CPU rendering, tracker music, MIDI, joystick etc.

Currently only CPU rendering is supported, athough SDL2 may give some sort of DirectX and OpenGL/GLES acceleration even on 2D.

Includes a demo of various engine features and a few sample programs that are supposed to be separate projects some day: CaveBombers, Pinball, RocketZ, PubLiippari (screensaver), Tetrex

The music in RocketZ sample program is [a remix made by Nuggumath](https://www.youtube.com/watch?v=o3TkUdJ8NlA) of one of the original Wings game music tunes called [PELIMUSA.S3M, made by Jussi Huhtala](https://www.youtube.com/watch?v=XKs5mkEpWuU).

Currently supported/tested operating systems and compilers:

MS-Windows (MinGW), GNU/Linux, GNU g++

Should compile into both 32 and 64 bit executable.

## Depencies

[SDL2](https://www.libsdl.org/download-2.0.php), [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/), [SDL2_image](https://www.libsdl.org/projects/SDL_image/), [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

Links to fonts used: [ModeNine](https://www.fontspace.com/grudnuk-creations/modenine), [xenosphere](https://www.fontspace.com/darrell-flood/xenosphere)

**NOTE:** 32 bit version, at least on MinGW, gives an error when trying to load a .PNG file. It says something about inflateValidate procedure, not sure why this is, probably a bug in some version of SDL2_image / libpng16-16.dll / zlib1.dll I guess...

![screenshot](http://titanix.net/~japek/rocketz/RocketZ_0.004.png)

You may download precompiled RocketZ binaries for Windows and Linux from [RocketZ homepage](http://titanix.net/~japek/rocketz/).