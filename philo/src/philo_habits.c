/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_habits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:32:51 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/23 13:16:34 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal);
	if (!check_and_print(philo, "is eating\n"))
	{
		ft_put_forks(philo);
		return (1);
	}
	if (ft_sleep(philo->content->time_to_eat, philo->content))
	{
		ft_put_forks(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->p_meals);
	philo->meals++;
	if (philo->content->number_of_meals != -1 \
		&& philo->meals >= philo->content->number_of_meals)
	{
		ft_put_forks(philo);
		pthread_mutex_unlock(&philo->p_meals);
		return (1);
	}
	ft_put_forks(philo);
	pthread_mutex_unlock(&philo->p_meals);
	return (0);
}

int	ft_philo_sleeping(t_philo *philo)
{
	if (!check_and_print(philo, "is sleeping\n"))
		return (1);
	if (ft_sleep(philo->content->time_to_sleep, philo->content))
		return (1);
	return (0);
}

int	ft_philo_thinking(t_philo *philo)
{
	if (!check_and_print(philo, "is thinking\n"))
		return (1);
	return (0);
}

int	ft_philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->content->dead);
	if (philo->content->is_die)
	{
		pthread_mutex_unlock(&philo->content->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->content->dead);
	return (0);
}

int	ft_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = &philo->left_fork->fork;
	second_fork = &philo->right_fork->fork;
	pthread_mutex_lock(first_fork);
	if (!check_and_print(philo, "has taken a fork\n"))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	pthread_mutex_lock(second_fork);
	if (!check_and_print(philo, "has taken a fork\n"))
	{
		ft_put_forks(philo);
		return (1);
	}
	return (0);
}
