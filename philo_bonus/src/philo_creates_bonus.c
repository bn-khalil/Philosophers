/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creates_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:09:51 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/20 14:57:41 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

// t_philo *ft_lstnew_philo(int philo_number)
// {
// 	t_philo	*head;

// 	head = malloc(sizeof(t_philo));
// 	if (!head)
// 		return (NULL);
// 	head->meals = 0;
// 	head->time_last_meal = 0;
//     head->id = philo_number;
// 	head->next = NULL;
//     head->process = 0;
// 	head->content = NULL;
// 	head->last_meal_name = ft_strjoin("/last_meal_", ft_itoa(head->id));
// 	sem_unlink(head->last_meal_name);
// 	head->last_meal = sem_open(head->last_meal_name, O_CREAT, 0644, 1);
// 	if (head->last_meal == SEM_FAILED)
// 	{
// 		// close even the open semaphores too
// 		// close all the sems the dead and other in 
// 		exit(EXIT_FAILURE);
// 	}
// 	head->p_meals_name = ft_strjoin("/p_meal_", ft_itoa(head->id));
// 	sem_unlink(head->p_meals_name);
// 	head->p_meals = sem_open(head->p_meals_name, O_CREAT, 0644, 1);
// 	if (head->p_meals == SEM_FAILED)
// 	{
// 		// close even the open semaphores too
// 		// close all the sems the dead and other in 
// 		exit(EXIT_FAILURE);
// 	}
// 	return (head);
// }

// void	ft_lstadd_back_philo(t_philo **lst, t_philo *new)
// {
// 	t_philo	*head;

// 	if (!lst || !new)
// 		return ;
// 	if (*lst != NULL)
// 	{
// 		head = *lst;
// 		while (head->next != NULL)
// 			head = head->next;
// 		head->next = new;
// 	}
// 	else
// 		*lst = new;
// }

// void create_philos(t_container *content)
// {
//     int         i;
//     if (!content)
//         return ;
//     i = 0;
//     while (++i <= content->number_of_philos)
//         ft_lstadd_back_philo(&content->all_philos, ft_lstnew_philo(i));
// }
