#include "headers.h"

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
