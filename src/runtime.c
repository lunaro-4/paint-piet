#include "headers.h"
#include "paint-piet.h"

#define MAX_COLOR 0xff
#define MID_COLOR 0x00

void pointer_bump (struct pointer *pointer)
{
	if (pointer->cc_switched){
		switch (pointer->DP) {
			case DP_RIGHT:
				pointer->DP = DP_DOWN;
				break;
			case DP_DOWN:
				pointer->DP = DP_LEFT;
				break;
			case DP_LEFT:
				pointer->DP = DP_UP;
				break;
			case DP_UP:
				pointer->DP = DP_RIGHT;
		} // pointer->CC = CC_RIGHT; // apparantly, it should not reset the CC on DP change
	}
	else 
		switch (pointer->CC) {
			case CC_LEFT:
				pointer->CC = CC_RIGHT;
				break;
			case CC_RIGHT:
				pointer->CC = CC_LEFT;
				break;
		}

	pointer->cc_switched = !pointer->cc_switched;
}

bool move_pointer(int *y, int *x, int *new_y, int *new_x, int height, int width, int map[][width], enum direction *dp, enum moves *cc, int *bumps) 
{
	switch (*dp) {
		case DP_RIGHT:
			*new_y = *y;
			*new_x = *x + 1;
			break;
		case DP_DOWN:
			*new_y = *y + 1;
			*new_x = *x;
			break;
		case DP_LEFT:
			*new_y = *y;
			*new_x = *x - 1;
			break;
		case DP_UP:
			*new_y = *y - 1;
			*new_x = *x;
			break;
	}

	if (*new_y < 0 || *new_y >= height || *new_x < 0 || *new_x >= width ||
			map[*new_y][*new_x] == BLACK_INDEX)
	{
		(*bumps)++;
		*new_y = *y;
		*new_x = *x;
		return true;
	}
	return false;
}

void process_pointer(int *y, int *x, int height, int width, int map[][width], struct pointer *pointer, struct codel *codel_array[], int *bumps)
{

	int new_y, new_x;

	enum direction *dp = &pointer->DP;
	enum moves *cc = &pointer->CC;
	bool bumped = move_pointer(y, x, &new_y, &new_x, height, width, map, dp, cc, bumps);
	if (bumped) pointer_bump(pointer);

	int current_codel_id = map[*y][*x];
	int next_codel_id = map[new_y][new_x];


	if (!bumped && next_codel_id == WHITE_INDEX)
	{
		bool is_white = true;
		int local_x = *x, local_y = *y;
		while (is_white)
		{
			bool bumped = move_pointer(&local_y, &local_x, &new_y, &new_x, height, width, map, dp, cc, bumps);
			if (bumped) pointer_bump(pointer);
			local_y = new_y;
			local_x = new_x;
			is_white = map[local_y][local_x] == WHITE_INDEX;
		} 
		*y = local_y;
		*x = local_x;
		return;
	}

	struct codel *chosen_codel;
	if (bumped)
	{
		chosen_codel =  codel_array[current_codel_id];
	}
	else 
	{
		chosen_codel =  codel_array[next_codel_id];
		pointer->codels[0] = current_codel_id;
		pointer->codels[1] = next_codel_id;
		*bumps = 0;
	}
	
	if (*dp == DP_RIGHT || *dp == DP_LEFT)
	{
		*x = chosen_codel->corner_points[*dp][0];
		*y = chosen_codel->corner_points[*dp][*cc];
	}
	else 
	{
		*y = chosen_codel->corner_points[*dp][0];
		*x = chosen_codel->corner_points[*dp][*cc];
	}

	
}

int get_color_light (struct color *color)
{
	if (color->red > 0 && color->green > 0 && color->blue > 0)
		return PIET_LIGHT;
	else
	if (color->red < 0xff && color->green < 0xff && color->blue < 0xff)
		return PIET_DARK;
	else
		return PIET_NORMAL;
}

int get_color_hue (struct color *color, enum piet_light light)
{
	bool red = false, green = false, blue = false;
	/* TODO:
	 *	LIGHT == MAX_COLOR
	 *	NORMAL > MID_COLOR
	 *	DARK <= MID_COLOR
	 *	*/
	switch (light) {
		case PIET_LIGHT:
			;
		case PIET_NORMAL:
			if (color->red == MAX_COLOR)
				red = true;
			if (color->green == MAX_COLOR)
				green = true;
			if (color->blue == MAX_COLOR)
				blue = true;
			break;
		case PIET_DARK:
			if (color->red >= MID_COLOR)
				red = true;
			if (color->green >= MID_COLOR)
				green = true;
			if (color->blue >= MID_COLOR)
				blue = true;

	}
	// int result = 0;

	/* if (red)
		result += PIET_RED;
	if (green)
		result += PIET_GREEN;
	if (blue)
		result += PIET_BLUE; */

	if (red && green)
		return PIET_YELLOW;
	if (green && blue)
		return PIET_CYAN;
	if (blue && red)
		return PIET_MAGENTA;
	if (red)
		return PIET_RED;
	if (green)
		return PIET_GREEN;
	if (blue)
		return PIET_BLUE;

	perror("No hue match found!");
	return -1;

}

void count_steps (struct color *a, struct color *b, int *hue_steps, int *light_steps)
{
	*hue_steps = *light_steps = 0;

	enum piet_hue a_hue = 0, b_hue = 0;
	enum piet_light a_light = 0, b_light = 0;


	a_light = get_color_light(a);
	b_light = get_color_light(b);

	printf("colors: \n R:\t%2x\t%2x\nG:\t%2x\t%2x\nB:\t%2x\t%2x\n", a->red, b->red, a->green, b->green, a->blue, b->blue);

	printf("lights: a: %i, b: %i\n", a_light, b_light);

	a_hue = get_color_hue(a, a_light);
	b_hue = get_color_hue(b, b_light);

	printf("hue: a: %i, b: %i\n", a_hue, b_hue);

	int local_hue_steps = b_hue - a_hue,
		local_light_steps = b_light - a_light;

	if (local_light_steps < 0)
		local_light_steps += 2;

	*light_steps = local_light_steps;

	if (local_hue_steps < 0)
		local_hue_steps += 5;

	*hue_steps = local_hue_steps;



	/* int r_diff = a->red - b->red, g_diff = a->green - b->green, b_diff = a->blue - a->blue;

	if ((r_diff >= 0 && g_diff >= 0) || (g_diff >= 0 && b_diff >= 0) || (b_diff >= 0 && r_diff >= 0))
	{
		++*hue_steps;
	} */

}
