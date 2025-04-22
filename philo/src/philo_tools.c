/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:22:50 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/22 14:42:42 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long get_time()
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
    {
        ft_error("Error in time");
        return (-1);
    }
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int ft_sleep(long time, t_container *content)
{
    long te;

    te = get_time();
    while ((get_time() - te) < time)
    {
        pthread_mutex_lock(&content->dead);
        if (content->is_die)
        {
            pthread_mutex_unlock(&content->dead);
            return (1);
        }
        pthread_mutex_unlock(&content->dead);
        usleep(500);
    }
    return (0);
}

int check_and_print(t_philo *philo, char *message)
{
    pthread_mutex_lock(&philo->content->dead);
    if (philo->content->is_die)
    {
        pthread_mutex_unlock(&philo->content->dead);
        return (0);
    }
    pthread_mutex_lock(&philo->content->print);
    printf("%ld %d %s", get_time() - philo->content->started_time, \
    philo->id, message);
    pthread_mutex_unlock(&philo->content->print);
    pthread_mutex_unlock(&philo->content->dead);
    return (1);
}

int ft_wait(t_container *content, t_philo *philo, int flag)
{
    if (flag)
    {
        if (pthread_join(content->thread_monitor, NULL) != 0)
            return (ft_error("Error in join for threads!"), 1);
    }
    else
    {
        if (pthread_join(content->thread_monitor, NULL) != 0)
            return (ft_error("Error in join for threads!"), 1);
        philo = content->all_philos;
        while (philo)
        {
            if (pthread_join(philo->thread, NULL) != 0)
                return (ft_error("Error in join for threads!"), 1);
            philo = philo->next;
        }
    }
    return (0);  
}

void ft_put_forks(t_philo *philo)
{
    if (!philo || !philo->left_fork || !philo->right_fork)
        return ;
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
}