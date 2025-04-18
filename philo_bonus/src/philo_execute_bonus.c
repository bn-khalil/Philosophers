/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_execute_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:56:19 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/18 18:20:34 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int start_philo_action(t_container *content)
{
    t_philo *philos;

    philos = content->all_philos;
    while (philos)
    {
        philos->process = fork();
        if (philos->process != 0)
        {
            
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
