#include <stdlib.h>

#include "enemy.h"

shot_sentinel* create_shotlist(void)
{
	shot_sentinel *list;
	if(!(list = (shot_sentinel*) malloc (sizeof(shot_sentinel))))
		exit(1);

	list->first = NULL;
	list->last  = NULL;

	return list;
}

shot* remove_shot(shot* current, shot* previous, shot_sentinel *list)
{
	if (!current) 
		return NULL;
		
	if (previous == NULL)
		list->first = current->next;
	else 
		previous->next = current->next;

	if (current->next == NULL)
		list->last = previous;
		
	shot *next = current->next;
	free(current);
	
	return next;
}

void clean_shots(shot_sentinel *list){
	shot *p = (shot*) list->first;
	shot *q = NULL;

	while (p != NULL)
		p = remove_shot(p, q, list);
}

void update_shots(space *board, shot_sentinel *list){
	shot *p = (shot*) list->first;
	shot *q = NULL;
	while (p != NULL){
		if (p->trajectory == 1)
		{
			if (p->position_y == board->max_y)
				p = remove_shot(p, q, list);
			else
			{
				p->position_y++;
				q = p;
				p = p->next;
			}
		}
	}
}

shot* straight_shot(space *board, shot_sentinel *list, enemy *shooter)
{
	shot *new_shot;
	if(!(new_shot = (shot*) malloc (sizeof(shot))))
		exit(2);

	new_shot->position_x = shooter->position_x;
	new_shot->position_y = shooter->position_y + 1;
	new_shot->trajectory = 1;
	new_shot->next = NULL;

	if(!list->first) 
		list->first = new_shot;
	else 
		list->last->next = new_shot;
	list->last = new_shot;

	board->map[new_shot->position_y][new_shot->position_x].entity = NULL;

	return new_shot;
}

int add_enemy(space *board, int position_y, int position_x){
	if(!board) 
		return 0;
	
	if(!(board->map[position_y][position_x].entity = (enemy*) malloc (sizeof(enemy))))
		exit(3);

	((enemy*) board->map[position_y][position_x].entity)->position_x = position_x;
	((enemy*) board->map[position_y][position_x].entity)->position_y = position_y;
	board->map[position_y][position_x].type = ENEMY;

	return 1;
}

int remove_enemy(space *board, int position_y, int position_x){
	if(!board || !board->map[position_y][position_x].entity) 
		return 0;

	free(board->map[position_y][position_x].entity);
	board->map[position_y][position_x].entity = NULL;
	board->map[position_y][position_x].type = 0;

	return 1;
}
