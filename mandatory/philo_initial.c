#include "philo.h"

void assign_forks_to_philo(t_container *content)
{
    t_philo *philo;
    t_fork  *fork;
    t_fork  *hold_first_fork;

    philo = content->all_philos;
    fork  = content->all_forks;
    hold_first_fork = fork;
    while (philo != NULL)
    {
        philo->left_fork = fork;
        if (philo->next && fork->next)
            philo->right_fork = fork->next;
        else
            philo->right_fork = hold_first_fork;
        philo = philo->next;
        fork  = fork->next;
    }
}

void create_philos(t_container *content)
{
    int         i;
    if (!content)
        return ;
    i = 1;
    while (i <= content->number_of_philos)
    {
        ft_lstadd_back_philo(&content->all_philos, ft_lstnew_philo(i));
        ft_lstadd_back_fork(&content->all_forks, ft_lstnew_fork(i));
        i++;
    }
}