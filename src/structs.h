#include <stdint.h>


#ifndef ENUMS
#define ENUMS

enum moves {
	CC_LEFT = 0, CC_RIGHT = 1
};

enum direction {
	 DP_RIGHT = 0, DP_DOWN = 1, DP_LEFT = 2, DP_UP = 3
};
#endif // !ENUMS

#ifndef STRUCTS
#define STRUCTS

struct color {
	int red;
	int green;
	int blue;
};

// struct point {
// 	uint32_t x;
// 	uint32_t y;
// };
// struct corner_point {
// 	int next_codels[2];
// };

struct codel {
	uint16_t size;
	struct color color;
	int corner_points[4][2];	
};

struct pointer {
	enum moves CC;
	enum direction DP;
};

#endif // !STRUCTS

#ifndef CONSTS
#define CONSTS

#define WHITE_INDEX 1
#define BLACK_INDEX 0

#define CODEL_ARRAY_SIZE 500



#endif // !CONSTS
