#include <stdint.h>

enum moves {
	CC_LEFT, CC_RIGHT
};

enum direction {
	DP_UP = 0, DP_RIGHT = 1, DP_DOWN = 2, DP_LEFT = 3
};

struct color {
	int red;
	int green;
	int blue;
};

struct point {
	uint32_t x;
	uint32_t y;
};
struct corner_point {
	struct point possible_move_coords[2];
};

struct codel {
	uint16_t size;
	uint16_t color;
	struct point corner_points[4];	
};

struct pointer {
	enum moves CC;
};
