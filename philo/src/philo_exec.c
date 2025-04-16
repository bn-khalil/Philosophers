/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:00 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/16 12:48:17 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long get_time()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
    {
        ft_error("Error in time");
    }
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_sleep(long time, t_container *content)
{

    long te;

    te = get_time();
    while ((get_time() - te) < time)
    {
        pthread_mutex_lock(&content->dead);
        if (content->is_die)
        {
            pthread_mutex_unlock(&content->dead);
            return ;
        }
        pthread_mutex_unlock(&content->dead);
        usleep(500);
    }
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
    printf("%ld %d %s", get_time() - philo->content->started_time, philo->id, message);
    pthread_mutex_unlock(&philo->content->print);
    pthread_mutex_unlock(&philo->content->dead);
    return (1);
}

void *philo_actions(void *data)
{
    t_philo *philo = (t_philo*)data;

    if (philo->id % 2 == 0)
        usleep(500);
    while (1)
    {
        pthread_mutex_lock(&philo->content->dead);
        if (philo->content->is_die)
        {
            pthread_mutex_unlock(&philo->content->dead);
            break ;
        }
        pthread_mutex_unlock(&philo->content->dead);

        pthread_mutex_lock(&philo->left_fork->fork);
        if (!check_and_print(philo, "has taken a fork\n"))
        {
            pthread_mutex_unlock(&philo->left_fork->fork);
            break ;
        }
        pthread_mutex_lock(&philo->right_fork->fork);
        if (!check_and_print(philo, "has taken a fork\n"))
        {
            pthread_mutex_unlock(&philo->left_fork->fork);
            pthread_mutex_unlock(&philo->right_fork->fork);
            break ;
        }

        pthread_mutex_lock(&philo->last_meal);
        philo->time_last_meal = get_time();
        pthread_mutex_unlock(&philo->last_meal);

        if (!check_and_print(philo, "is eating\n"))
        {
            pthread_mutex_unlock(&philo->left_fork->fork);
            pthread_mutex_unlock(&philo->right_fork->fork);
            break ;
        }

        ft_sleep(philo->content->time_to_eat, philo->content);

        pthread_mutex_lock(&philo->p_meals);
        philo->meals++;
        if (philo->content->number_of_meals != -1 && philo->meals >= philo->content->number_of_meals)
        {
            pthread_mutex_unlock(&philo->left_fork->fork);
            pthread_mutex_unlock(&philo->right_fork->fork);
            pthread_mutex_unlock(&philo->p_meals);
            break ;
        }
        pthread_mutex_unlock(&philo->p_meals);
        pthread_mutex_unlock(&philo->left_fork->fork);
        pthread_mutex_unlock(&philo->right_fork->fork);

        // sleep
        if (!check_and_print(philo, "is sleeping\n"))
            break ;
        ft_sleep(philo->content->time_to_sleep, philo->content);
        // thinking
        if (!check_and_print(philo, "is thinking\n"))
            break ;
    }
    return (NULL);
}


void only_one_phlio(t_container *content)
{
    printf("%ld %d has taken left fork\n", get_time() - content->started_time, content->all_philos->id);
    ft_sleep(content->time_to_die, content);
    pthread_mutex_lock(&content->dead);
    content->is_die = 1;
    printf("%ld %d died\n", get_time() - content->started_time, content->all_philos->id);
    pthread_mutex_unlock(&content->dead);
}

void *check_for_deads_o(void *data)
{
    t_container *content = (t_container *)data;
    t_philo *philo;
    long speded_time;
    int is_all_finish;

    while (1)
    {
        is_all_finish = 1;
        philo = content->all_philos;
        while (philo)
        {
            pthread_mutex_lock(&philo->last_meal);
            speded_time = get_time() - philo->time_last_meal;
            pthread_mutex_unlock(&philo->last_meal);
            if (speded_time > philo->content->time_to_die)
            {
                pthread_mutex_lock(&content->dead);
                if (!content->is_die)
                {
                    content->is_die = 1;
                    printf("%ld %d died\n", get_time() - content->started_time, philo->id);
                }
                pthread_mutex_unlock(&content->dead);
                return (NULL);
            }
            pthread_mutex_lock(&philo->p_meals);
            if (content->number_of_meals != -1 && philo->meals < content->number_of_meals)
                is_all_finish = 0;
            pthread_mutex_unlock(&philo->p_meals);
           philo = philo->next;
        }
        if (content->number_of_meals != -1 && is_all_finish)
        {
            pthread_mutex_lock(&content->dead);
            content->is_die = 1;
            pthread_mutex_unlock(&content->dead);
            return (NULL);
        }
        usleep(500);
    }
    return (NULL);
}

void start_actions(t_container *content)
{
    t_philo *philo = content->all_philos;

    if (!philo)
        return ;
    content->started_time = get_time();
    if (!philo->next)
    {
        only_one_phlio(content);
        return ;
    }
    while (philo)
    {
        pthread_mutex_lock(&philo->last_meal);
        philo->time_last_meal = content->started_time;
        pthread_mutex_unlock(&philo->last_meal);
        philo->content = content;
        if (pthread_create(&philo->thread, NULL, &philo_actions, philo) != 0)
            ft_error("Error in threads!");
        philo = philo->next;
    }

    if (pthread_create(&content->thread_monitor, NULL, &check_for_deads_o, content) != 0)
        ft_error("Error in threads!");
    if (pthread_join(content->thread_monitor, NULL) != 0)
        ft_error("Error in join for threads!");
    philo = content->all_philos;
    while (philo)
    {
        if (pthread_join(philo->thread, NULL) != 0)
            ft_error("Error in join for threads!");
        philo = philo->next;
    }
}
