#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    if(head == NULL){
    	return 0;
    }
    node *torotise = head;
    node *hare = head->next;
    
    while(hare != NULL && hare->next != NULL ){
    	if(torotise == hare){
	   return 1;
	}
	hare = hare->next->next;
	torotise = torotise->next;
    }
    return 0;
}
