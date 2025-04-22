/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:00 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/22 17:19:55 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *philo_actions(void *data)
{
    t_philo *philo = (t_philo*)data;

    if (philo->id % 2 == 0)
        usleep(500);
    while (1)
    {
        if (ft_philo_die(philo))
            break ;
        if (ft_take_forks(philo))
            break ;
        if (ft_philo_eating(philo))
            break ;
        if (ft_philo_sleeping(philo))
            break ;
        if (ft_philo_thinking(philo))
            break ;
    }
    return (NULL);
}


void *action_one(void *data)
{
    t_container *content;

    content = (t_container*)data;
    printf("%ld %d has taken left fork\n", get_time() - \
    content->started_time, content->all_philos->id);
    ft_sleep(content->time_to_die, content);
    pthread_mutex_lock(&content->dead);
    content->is_die = 1;
    printf("%ld %d died\n", get_time() - content->started_time, \
    content->all_philos->id);
    pthread_mutex_unlock(&content->dead);
    return (NULL);
}
void only_one_phlio(t_container *content)
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, &action_one, content) != 0)
        ft_error("Error in threads!");
    if (pthread_join(thread, NULL) != 0)
        ft_error("Error in join!");
}

int death_logic(t_container *content, t_philo *philo, int *is_all_finish)
{    
    pthread_mutex_lock(&philo->p_meals);
    if (content->number_of_meals != -1 && philo->meals \
    < content->number_of_meals)
        (*is_all_finish) = 0;
    pthread_mutex_unlock(&philo->p_meals);
    if (content->all_finish)
        return (0);
    pthread_mutex_lock(&philo->last_meal);
    if (get_time() - philo->time_last_meal > philo->content->time_to_die)
    {
        pthread_mutex_lock(&content->dead);
        if (!content->is_die || !content->all_finish)
        {
            pthread_mutex_lock(&content->print);
            content->is_die = 1;
            printf("%ld %d died\n", get_time() - content->started_time\
            , philo->id);
            pthread_mutex_unlock(&content->print);
        }
        pthread_mutex_unlock(&content->dead);
        pthread_mutex_unlock(&philo->last_meal);
        return (1);
    }
    pthread_mutex_unlock(&philo->last_meal);
    return (0);
}

void *check_for_deaths(void *data)
{
    t_container *content = (t_container *)data;
    t_philo *philo;
    int is_all_finish;

    while (1)
    {
        is_all_finish = 1;
        philo = content->all_philos;
        while (philo)
        {
            if (death_logic(content, philo, &is_all_finish))
                return (NULL);
           philo = philo->next;
        }
        if (content->number_of_meals != -1 && is_all_finish)
        {
            pthread_mutex_lock(&content->dead);
            content->all_finish = 1;
            pthread_mutex_unlock(&content->dead);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

int start_actions(t_container *content)
{
    t_philo *philo;

    philo = content->all_philos;
    content->started_time = get_time();
    if (!philo->next)
        return (only_one_phlio(content), 0);
    while (philo)
    {
        pthread_mutex_lock(&philo->last_meal);
        philo->time_last_meal = content->started_time;
        pthread_mutex_unlock(&philo->last_meal);
        philo->content = content;
        if (pthread_create(&philo->thread, NULL, &philo_actions, philo) != 0)
        {
            ft_wait(content, content->all_philos, 1);
            return (ft_error("Error in threads!"), 1);
        }
        philo = philo->next;
    }
    if (pthread_create(&content->thread_monitor, NULL, \
    &check_for_deaths, content) != 0)
        return (ft_error("Error in threads!"), 1);
    if (ft_wait(content, philo, 0))
        return (1);
    return (0);
}
