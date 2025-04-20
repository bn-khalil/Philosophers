/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_habits_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:32:51 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/20 20:59:27 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

// int ft_take_forks(t_philo *philo, t_container *content)
// {
//     sem_wait(content->fork);
//     if (!check_and_print(philo, "has taken a fork\n"))
//     {
//         sem_post(content->fork);
//         return (1);
//     }
//     sem_wait(content->fork);
//     if (!check_and_print(philo, "has taken a fork\n"))
//     {
//         ft_put_forks(content);
//         return (1);
//     }
//     return (0);
// }

// int ft_philo_eating(t_philo *philo, t_container *content)
// {
//     sem_wait(philo->last_meal);
//     philo->time_last_meal = get_time();
//     sem_post(philo->last_meal);
//     if (!check_and_print(philo, "is eating\n"))
//     {
//         ft_put_forks(content);
//         return (1);
//     }
//     if (ft_sleep(content->time_to_eat, content))
//     {
//         ft_put_forks(content);
//         return (1);
//     }
//     ft_put_forks(content);
//     sem_wait(philo->p_meals);
//     philo->meals++;
//     sem_post(philo->p_meals);
//     if (content->number_of_meals != -1 && philo->meals >= content->number_of_meals)
//         return (1);
//     return (0);
// }

// int ft_philo_sleeping(t_philo *philo, t_container *content)
// {
//     if (!check_and_print(philo,"is sleeping\n"))
//         return (1);
//     if (ft_sleep(philo->content->time_to_sleep, content))
//         return (1);
//     return (0);
// }

// int ft_philo_thinking(t_philo *philo, t_container *content)
// {
//     (void)content;
//     if (!check_and_print(philo,"is thinking\n"))
//         return (1);
//     return (0);
// }

// int ft_philo_die(t_container *content)
// {
//     sem_wait(content->dead);
//     if (content->is_die > 0)
//     {
//         sem_post(content->dead);
//         return (1);
//     }
//     sem_post(content->dead);
//     return (0);
// }
