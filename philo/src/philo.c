/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:12 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/23 15:46:39 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_free_philos(t_philo *philo)
{
	t_philo	*current;
	t_philo	*next;

	current = philo;
	while (current)
	{
		next = current->next;
		pthread_mutex_destroy(&current->p_meals);
		pthread_mutex_destroy(&current->last_meal);
		free(current);
		current = next;
	}
}

static void	ft_free_forks(t_fork *fork)
{
	t_fork	*current;
	t_fork	*next;

	current = fork;
	while (current)
	{
		next = current->next;
		pthread_mutex_destroy(&current->fork);
		free(current);
		current = next;
	}
}

static void	ft_free_all(t_container *content)
{
	if (!content)
		return ;
	if (content->all_philos)
		ft_free_philos(content->all_philos);
	if (content->all_forks)
		ft_free_forks(content->all_forks);
	pthread_mutex_destroy(&content->dead);
	pthread_mutex_destroy(&content->print);
}

static int	argument_parse_init(t_container *content, char **av)
{
	if (!content)
		return (1);
	if (parse_content(content, av))
		return (1);
	create_philos(content);
	if (!content->all_forks || !content->all_philos)
		return (1);
	if (assign_forks_to_philo(content))
		return (1);
	if (start_actions(content))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_container	content;

	if (ac < 5 || ac > 6)
	{
		ft_error("Invalid number of arguments!");
		return (1);
	}
	memset(&content, 0, sizeof(t_container));
	if (argument_parse_init(&content, av))
		return (ft_free_all(&content), 1);
	return (ft_free_all(&content), 0);
}
