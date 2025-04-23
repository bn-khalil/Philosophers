/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initial.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:03 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/23 15:48:32 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	init_lockses(t_philo *philo, t_fork *forks)
{
	t_philo	*p;
	t_fork	*f;

	if (!philo || !forks)
		return (1);
	p = philo;
	f = forks;
	while (p && f)
	{
		if (pthread_mutex_init(&p->last_meal, NULL) != 0 \
			|| pthread_mutex_init(&p->p_meals, NULL) != 0 \
			|| pthread_mutex_init(&f->fork, NULL) != 0)
		{
			ft_error("Failed to init mutex");
			return (1);
		}
		p = p->next;
		f = f->next;
	}
	return (0);
}

int	assign_forks_to_philo(t_container *content)
{
	t_philo	*philo;
	t_fork	*fork;
	t_fork	*hold_first_fork;

	philo = content->all_philos;
	fork = content->all_forks;
	if (init_lockses(philo, fork))
		return (1);
	hold_first_fork = fork;
	while (philo && fork)
	{
		philo->left_fork = fork;
		if (philo->next && fork->next)
			philo->right_fork = fork->next;
		else
			philo->right_fork = hold_first_fork;
		philo = philo->next;
		fork = fork->next;
	}
	return (0);
}

void	*action_one(void *data)
{
	t_container	*content;

	content = (t_container *)data;
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
