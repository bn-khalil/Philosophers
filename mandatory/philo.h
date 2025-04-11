/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:35:21 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/11 10:45:17 by kben-tou         ###   ########.fr       */
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
    struct          s_fork *next;
}                   t_fork;


typedef struct      s_philo
{
    int             id;
    pthread_t       thread;
    p_status        status;
    long            time_last_meal;
    t_fork          *left_fork;
    t_fork          *right_fork;
    int             meals;
    struct          s_philo *next;
}                   t_philo;

typedef struct      s_container
{
    t_philo         *all_philos;
    t_philo         *all_forks;
    int             number_of_meals;
    long            number_of_philos;
    long            time_to_eat;
    long            time_to_die;
    long            time_to_sleep;
}                   t_container;

void ft_error(char *err);

#endif