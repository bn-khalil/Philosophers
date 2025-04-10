/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:35:21 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/10 18:09:09 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>

typedef enum status
{
    P_THINK,
    P_EAT,
    P_SLEEP,
    P_DIE
} p_status;

typedef struct      s_fork
{
    int             fork_id;
    pthread_mutex_t fork;
}                   t_fork;


typedef struct      s_philo
{
    int             id;
    pthread_t       thread;
    p_status        status;
    size_t          time_last_meal;
    t_fork          *left_fork;
    t_fork          *right_fork;
}                   t_philo;

typedef struct      s_container
{
    t_philo         *all_philos;
    t_philo         *all_forks;
    int             number_of_meals;
    size_t          number_of_philos;
    size_t          time_to_eat;
    size_t          time_to_die;
    size_t          time_to_sleep;
}                   t_container;

void ft_error(char *err);

#endif