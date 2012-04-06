/*
 * function frees memory of the node 
 * copyright ï¿½ 2012 Adam Jirasek
 */
 
#include "Header.h"
#include "format_type.h"
#include "Mount.h"


extern void Warning(const char *);
extern SIZE_T rm_list(int, node_t **);
extern int Free(node_t **);
extern int Cat(node_t *, char * , ...);

/*
 * this function deletes the master head node.
 * before doing so, remove all data sets in this node and 
 * then remove it.
 */

int Umount(node_t **List)
{
/*
 * delete everything in **List node
 */
	printf("Unmounting node %s at %p\n", (*List)-> name, (*List));
/*
 * when calling rm_list, specify 2 as if the function was not called initially
 * When called initially, the function consideres List as a parent dir and does not remove it
 * In this routine, the function is supposed to remove List so it needs to be called with 2
 */ 
	if( rm_list(2, List) < 0){
		Error("Unable to unmount node %s at %p\n", (*List)-> name, (*List));
		return -1;
	}
	printf("Unmounting finished\n");

	return 1;
}