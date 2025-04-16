/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initial.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:03 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/16 15:17:29 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int init_lockses(t_philo *philo, t_fork *forks)
{
    while (philo && forks)
    {
        if (pthread_mutex_init(&philo->last_meal, NULL) != 0 \
        || pthread_mutex_init(&philo->p_meals, NULL) != 0 \
        || pthread_mutex_init(&forks->fork, NULL) != 0 \
        || 
        ){
            ft_error("Failed to init mutex");
            return (1);
        }
        philo = philo->next;
        forks = forks->next;
    }
    return (0);
}

void assign_forks_to_philo(t_container *content)
{
    t_philo *philo;
    t_fork  *fork;
    t_fork  *hold_first_fork;

    philo = content->all_philos;
    fork  = content->all_forks;
    if (init_lockses(&philo, &fork));
        return ;
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