/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_execute_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:56:19 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/19 10:18:07 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int philo_actions(t_philo *philo)
{
    if (philo->id % 2 == 0)
        usleep(500);
    while (1)
    {
        // if (ft_philo_die(philo))
        //     return (1);        
        if (ft_take_forks(philo))
            return (1);
        if (ft_philo_eating(philo))
            return (1);
        if (ft_philo_sleeping(philo))
            return (1);
        if (ft_philo_thinking(philo))
            return (1);
    }
    return (0);
}

void *check_for_deaths(void *data)
{
    t_philo *philo = (t_philo *)data;
    // int is_all_finish;

    while (1)
    {
        // is_all_finish = 1;
        // philo = content->all_philos;
        // while (philo)
        // {
        //     if (death_logic(content, philo, &is_all_finish))
        //         return (NULL);
        //    philo = philo->next;
        // }
        // if (content->number_of_meals != -1 && is_all_finish)
        // {
        //     pthread_mutex_lock(&content->dead);
        //     content->is_die = 1;
        //     pthread_mutex_unlock(&content->dead);
        //     return (NULL);
        // }
        printf("monitor is runing for philo (%d)\n", philo->id);
        usleep(10000);
    }
    return (NULL);
}

int start_philo_action(t_container *content)
{
    t_philo *philos;

    philos = content->all_philos;
    while (philos)
    {
        philos->process = fork();
        if (philos->process < 0)
            ;//free and kill
        if (philos->process == 0)
        {
            if (pthread_create(&philos->monitor, NULL, check_for_deaths, philos))
            //     ;// check here too
            philo_actions(philos);
            exit(0);
        }
        philos = philos->next;
    }
    philos = content->all_philos;
    while (philos)
    {
        waitpid(philos->process, NULL, 0);
        philos = philos->next;
    }
    return (0);
}
