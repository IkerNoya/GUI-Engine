#ifndef FRAME_H
#define FRAME_H

struct Coord {
	float u;
	float v;
};

struct Frame {
	Coord frameCoords[4]; // for each side of a quad texture?
};

#endif // !FRAME_H

