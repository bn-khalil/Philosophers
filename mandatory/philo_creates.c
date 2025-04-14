#include "philo.h"

t_philo *ft_lstnew_philo(int philo_number)
{
	t_philo	*head;

	head = malloc(sizeof(t_philo));
	if (!head)
		return (NULL);
	head->meals = 0;
	head->time_last_meal = 0;
    head->id = philo_number;
	head->next = NULL;
    head->left_fork = NULL;
    head->right_fork = NULL;
    head->thread = NULL;
	head->content = NULL;
	return (head);
}

t_fork *ft_lstnew_fork(int philo_number)
{
	t_fork	*head;

	head = malloc(sizeof(t_fork));
	if (!head)
		return (NULL);
    head->fork_id   = philo_number;
    if (pthread_mutex_init(&head->fork, NULL) != 0)
    {
        // free all forks and philos
        ft_error("Failed to init mutex");
    }
	head->next = NULL;
	return (head);
}

void	ft_lstadd_back_philo(t_philo **lst, t_philo *new)
{
	t_philo	*head;

	if (!lst || !new)
		return ;
	if (*lst != NULL)
	{
		head = *lst;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
	else
		*lst = new;
}

void	ft_lstadd_back_fork(t_fork **lst, t_fork *new)
{
	t_fork	*head;

	if (!lst || !new)
		return ;
	if (*lst != NULL)
	{
		head = *lst;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
	else
		*lst = new;
}
