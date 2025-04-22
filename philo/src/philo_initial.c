/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initial.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:03 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/22 12:14:46 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int init_lockses(t_philo *philo, t_fork *forks)
{
    t_philo *p;
    t_fork *f;

    if (!philo || !forks)
        return (1);
    p = philo;
    f = forks;
    while (p && f)
    {
        if (pthread_mutex_init(&p->last_meal, NULL) != 0 \
        || pthread_mutex_init(&p->p_meals, NULL) != 0 \
        || pthread_mutex_init(&f->fork, NULL) != 0 )
        {
            ft_error("Failed to init mutex");
            return (1);
        }
        p = p->next;
        f = f->next;
    }
    return (0);
}

int assign_forks_to_philo(t_container *content)
{
    t_philo *philo;
    t_fork  *fork;
    t_fork  *hold_first_fork;

    philo = content->all_philos;
    fork  = content->all_forks;
    if (init_lockses(philo, fork))
        return (1);
    hold_first_fork = fork;
    while (philo && fork)
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

void create_philos (t_container *content)
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
