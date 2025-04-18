/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initial_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:03 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/18 19:49:22 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int init_lockses(t_philo *philo, t_fork *forks)
{
    t_philo *p;
    t_fork *f;

    p = philo;
    f = forks;
    while (p && f)
    {
        f->fork_name = ft_strjoin("/fork_", ft_itoa(f->fork_id));
        f->fork = sem_open(f->fork_name, O_CREAT, 0644, 1);
        if (f->fork == SEM_FAILED)
        {
            // close even the open semaphores too
            // close all the sems the dead and other in 
            exit(EXIT_FAILURE);
        }
        p->last_meal_name = ft_strjoin("/last_meal_", ft_itoa(p->id));
        p->last_meal = sem_open(p->last_meal_name, O_CREAT, 0644, 1);
        if (p->last_meal == SEM_FAILED)
        {
            // close even the open semaphores too
            // close all the sems the dead and other in 
            exit(EXIT_FAILURE);
        }
        p->p_meals_name = ft_strjoin("/p_meal_", ft_itoa(p->id));
        p->p_meals = sem_open(p->p_meals_name, O_CREAT, 0644, 1);
        if (p->p_meals == SEM_FAILED)
        {
            // close even the open semaphores too
            // close all the sems the dead and other in 
            exit(EXIT_FAILURE);
        }
        p = p->next;
        f = f->next;
    }
    return (0);
}

int assign_forks_to_philo(t_container *content)
{
    (void) content;
    t_philo *philo;
    t_fork  *fork;
    t_fork  *hold_first_fork;

    philo = content->all_philos;
    fork  = content->all_forks;
    if (init_lockses(philo, fork))
        return (1);
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
    return (0);
}

// void create_philos(t_container *content)
// {
//     int         i;
//     if (!content)
//         return ;
//     i = 1;
//     while (i <= content->number_of_philos)
//     {
//         ft_lstadd_back_philo(&content->all_philos, ft_lstnew_philo(i));
//         ft_lstadd_back_fork(&content->all_forks, ft_lstnew_fork(i));
//         i++;
//     }
// }
