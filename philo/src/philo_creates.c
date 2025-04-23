/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creates.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:09:51 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/23 23:41:38 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_philo	*ft_lstnew_philo(int philo_number)
{
	t_philo	*head;

	head = malloc(sizeof(t_philo));
	if (!head)
		return (NULL);
	memset(head, 0, sizeof(t_philo));
	head->id = philo_number;
	return (head);
}

static t_fork	*ft_lstnew_fork(int philo_number)
{
	t_fork	*head;

	head = malloc(sizeof(t_fork));
	if (!head)
		return (NULL);
	memset(head, 0, sizeof(t_fork));
	head->fork_id = philo_number;
	return (head);
}

static void	ft_lstadd_back_philo(t_philo **lst, t_philo *new)
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

static void	ft_lstadd_back_fork(t_fork **lst, t_fork *new)
{
	t_fork	*head;

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
	t_fork	*fork;

	if (!content)
		return ;
	i = 1;
	while (i <= content->number_of_philos)
	{
		philo = ft_lstnew_philo(i);
		if (!philo)
			return ;
		ft_lstadd_back_philo(&content->all_philos, philo);
		fork = ft_lstnew_fork(i);
		if (!fork)
			return ;
		ft_lstadd_back_fork(&content->all_forks, fork);
		i++;
	}
}
