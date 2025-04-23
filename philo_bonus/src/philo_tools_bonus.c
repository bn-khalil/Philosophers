/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:22:50 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/23 14:04:03 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_error("Error in time");
		exit(1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_sleep(long time)
{
	long	te;

	te = get_time();
	while ((get_time() - te) < time)
		usleep(100);
	return (0);
}

void	check_and_print(t_philo *philo, t_container *content, char *message)
{
	sem_wait(content->print);
	printf("%ld %d %s", get_time() - content->started_time, philo->id, message);
	sem_post(content->print);
}

void	clean_philo(t_philo *philo)
{
	if (philo)
	{
		if (philo->last_meal)
		{
			sem_close(philo->last_meal);
			sem_unlink(philo->last_meal_name);
		}
		if (philo->p_meals)
		{
			sem_close(philo->p_meals);
			sem_unlink(philo->p_meals_name);
		}
		if (philo->last_meal_name)
			free(philo->last_meal_name);
		if (philo->p_meals_name)
			free(philo->p_meals_name);
	}
}

void	clean_res(t_container *content)
{
	t_philo	*philo;
	t_philo	*tmp;

	philo = content->all_philos;
	if (content)
	{
		if (content->fork)
		{
			sem_close(content->fork);
			sem_unlink(FORKS);
		}
		if (content->print)
		{
			sem_close(content->print);
			sem_unlink(PRINT);
		}
		while (philo)
		{
			tmp = philo;
			philo = philo->next;
			clean_philo(tmp);
			free(tmp);
		}
		content->all_philos = NULL;
	}
}
