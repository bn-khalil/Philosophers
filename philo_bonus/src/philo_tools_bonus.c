/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:22:50 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/20 14:57:57 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long get_time()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
    {
        ft_error("Error in time");
    }
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int ft_sleep(long time, t_container *content)
{

    long te;
    (void)content;
    te = get_time();
    while ((get_time() - te) < time)
        usleep(500);
    return (0);
}

// int check_and_print(t_philo *philo, t_container *content, char *message)
// {
//     sem_wait(content->print);
//     printf("%ld %d %s", get_time() - content->started_time, \
//     philo->id, message);
//     sem_post(content->print);
//     return (1);
// }

void ft_put_forks(t_container *content)
{
    sem_post(content->fork);
    sem_post(content->fork);
}