#include <stdbool.h>
#include <stdint.h>


#ifndef ENUMS
#define ENUMS

enum moves {
	CC_LEFT = 1, CC_RIGHT = 2
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
	int codels[2]; // old & new
	enum direction DP;
	enum moves CC;
	bool cc_switched;
};

#endif // !STRUCTS

#ifndef CONSTS
#define CONSTS

#define WHITE_INDEX 1
#define BLACK_INDEX 0

const struct color 
p_lr = {0xff, 0xc0, 0xc0},
p_r = {0xff, 0x00, 0x00},
p_dr = {0xc0, 0x00, 0x00},
p_ly = {0xff, 0xff, 0xc0},
p_y = {0xff, 0xff, 0x00},
p_dy = {0xc0, 0xc0, 0x00},
p_lg = {0xc0, 0xff, 0xc0},
p_g = {0x00, 0xff, 0x00},
p_dg = {0x00, 0xc0, 0x00},
p_lc = {0xc0, 0xff, 0xff},
p_c = {0x00, 0xff, 0xff},
p_dc = {0x00, 0xc0, 0xc0},
p_lb = {0xc0, 0xc0, 0xff},
p_b = {0x00, 0x00, 0xff},
p_db = {0x00, 0x00, 0xff},
p_lm = {0xff, 0xc0, 0xff},
p_m = {0xff, 0x00, 0xff},
p_dm = {0xc0, 0x00, 0xc0};


#define CODEL_ARRAY_SIZE 500

#define max(x, y) ((x > y) ? x : y)
#define min(x, y) ((x < y) ? x : y)

#define INIT_CORNER_POINTS(corner_points, y, x)  corner_points[0][0] = y; corner_points[0][1] = y; corner_points[1][0] = x; corner_points[1][1] = x; corner_points[2][0] = y; corner_points[2][1] = y; corner_points[3][0] = x; corner_points[3][1] = x;

#define RESOLVE_CORNER_POINTS(corner_points, y, x) corner_points[0][0] = min(corner_points[0][0], y); corner_points[0][1] = max(corner_points[0][0], y); corner_points[1][0] = max(corner_points[0][0], x); corner_points[1][1] = min(corner_points[0][0], x); corner_points[2][0] = max(corner_points[0][0], y); corner_points[2][1] = min(corner_points[0][0], y); corner_points[3][0] = min(corner_points[0][0], x); corner_points[3][1] = max(corner_points[0][0], x);
#endif // !CONSTS
