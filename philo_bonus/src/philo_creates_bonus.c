/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creates_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:09:51 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/23 14:06:58 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

t_philo	*ft_lstnew_philo(int philo_number)
{
	t_philo	*head;
	char	*hold;

	head = malloc(sizeof(t_philo));
	if (!head)
		return (NULL);
	head->id = philo_number;
	hold = ft_itoa(head->id);
	head->last_meal_name = ft_strjoin("/last_meal_", hold);
	sem_unlink(head->last_meal_name);
	head->last_meal = sem_open(head->last_meal_name, O_CREAT, 0644, 1);
	if (head->last_meal == SEM_FAILED)
		return (free(hold), NULL);
	head->p_meals_name = ft_strjoin("/p_meal_", hold);
	sem_unlink(head->p_meals_name);
	head->p_meals = sem_open(head->p_meals_name, O_CREAT, 0644, 1);
	if (head->p_meals == SEM_FAILED)
		return (free(hold), NULL);
	free(hold);
	return (head);
}

void	ft_lstadd_back_philo(t_philo **lst, t_philo *new)
{
	t_philo	*head;

	if (!lst || !new)
		return ;
	if (*lst != NULL)
	{
		head = *lst;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
	else
		*lst = new;
}

void	create_philos(t_container *content)
{
	int		i;
	t_philo	*philo;

	if (!content)
		return ;
	i = 0;
	while (++i <= content->number_of_philos)
	{
		philo = ft_lstnew_philo(i);
		if (!philo)
		{
			clean_res(content);
			return ;
		}
		ft_lstadd_back_philo(&content->all_philos, philo);
	}
}

void	ft_kill(t_container *content)
{
	t_philo	*philo;

	philo = content->all_philos;
	while (philo)
	{
		if (philo->monitor)
			pthread_detach(philo->monitor);
		if (philo->process > 0)
			kill(philo->process, SIGKILL);
		philo = philo->next;
	}
	exit(0);
}

void	check_is_die(t_philo *philo)
{
	long	last_meal;

	sem_wait(philo->last_meal);
	last_meal = philo->time_last_meal;
	sem_post(philo->last_meal);
	if (philo->content->time_to_die < get_time() - last_meal)
	{
		sem_wait(philo->content->print);
		printf("%ld %d %s", get_time() - philo->content->started_time, \
			philo->id, "died\n");
		exit(1);
	}
}
