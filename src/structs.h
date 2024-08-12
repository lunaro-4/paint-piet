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
	int corner_points[4][3];	
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

#define max(x, y) ((x > y) ? x : y)
#define min(x, y) ((x < y) ? x : y)

#define INIT_CORNER_POINTS(corner_points, y, x)  corner_points[0][0] = y; corner_points[0][1] = y; corner_points[1][0] = x; corner_points[1][1] = x; corner_points[2][0] = y; corner_points[2][1] = y; corner_points[3][0] = x; corner_points[3][1] = x;

#define RESOLVE_CORNER_POINTS(corner_points, y, x) corner_points[0][0] = min(corner_points[0][0], y); corner_points[0][1] = max(corner_points[0][0], y); corner_points[1][0] = max(corner_points[0][0], x); corner_points[1][1] = min(corner_points[0][0], x); corner_points[2][0] = max(corner_points[0][0], y); corner_points[2][1] = min(corner_points[0][0], y); corner_points[3][0] = min(corner_points[0][0], x); corner_points[3][1] = max(corner_points[0][0], x);
#endif // !CONSTS
