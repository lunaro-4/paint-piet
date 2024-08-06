#include <stdint.h>
struct color {
	int red;
	int green;
	int blue;
};

struct codel {
	uint16_t size;
	struct color color;
};
