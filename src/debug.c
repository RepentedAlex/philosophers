#include "debug.h"

void	dump_node(t_philosopher *node)
{
	printf("Node ID: %d ; Address: %p\n", node->id, node);
	printf("Node [%d] state: %d\n", node->id, node->state);
	printf("Node [%d]'s last meal: %ld\n", node->id, node->last_meal);
	printf("Node [%d]'s fork state: %d\n", node->id, node->fork_state);
	printf("Node [%d]'s prev node's address: %p\n", node->id, node->prev);
	printf("Node [%d]'s next node's address: %p\n", node->id, node->next);
}

void	review_list(t_philosopher **head)
{
	t_philosopher	*nav;

	nav = *head;
	dump_node(nav);
	nav = nav->next;
	while (nav != *head)
	{
		printf("\n");
		dump_node(nav);
		nav = nav->next;
	}
}

void	dump_frame(t_frame *frame)
{
	printf("\nReviewing frame...\n\n");
	printf("Number of philosophers: [%d]\n", frame->nb_of_philo);
	printf("Time to die (in ms): [%ld]\n", frame->time_to_die);
	printf("Time to eat (in ms): [%ld]\n", frame->time_to_eat);
	printf("Time to sleep (in ms): [%ld]\n", frame->time_to_sleep);
	printf("Eat limit: [%d]\n", frame->nb_time_eat);
	if (frame->head)
		(printf("\nNow reviewing list:\n"), review_list(&frame->head));
	else
		printf("\nThere is no initialised linked list!\n");
}