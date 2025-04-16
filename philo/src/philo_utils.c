/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:09 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/16 14:17:49 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

long	long_ft_atoi(const char *str)
{
	int		i;
	long	store;
	int		si;

	i = 0;
	si = 1;
	store = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			si *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		store = store * 10 + (str[i++] - '0');
	return (store * si);
}

void ft_free_philos(t_philo *philo)
{
    t_philo *current = philo;
    t_philo *next;

    while (current)
    {
        next = current->next;
		pthread_mutex_destroy(&philo->p_meals);
		pthread_mutex_destroy(&philo->last_meal);
        free(current);
        current = next;
    }
}

void ft_free_forks(t_fork *fork)
{
    t_fork *current = fork;
    t_fork *next;

    while (current)
    {
        next = current->next;
		pthread_mutex_destroy(&current->fork);
        free(current);
        current = next;
    }
}

void ft_free_all(t_container *content)
{
	ft_free_philos(content->all_philos);
	ft_free_forks(content->all_forks);
	pthread_mutex_destroy(&content->dead);
	pthread_mutex_destroy(&content->print);
}