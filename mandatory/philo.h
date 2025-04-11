/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:35:21 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/11 12:25:53 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>

typedef struct      s_fork
{
    int             fork_id;
    pthread_mutex_t fork;
    struct          s_fork *next;
}                   t_fork;


typedef struct      s_philo
{
    int             id;
    pthread_t       thread;
    long            time_last_meal;
    t_fork          *left_fork;
    t_fork          *right_fork;
    int             meals;
    struct          s_philo *next;
}                   t_philo;

typedef struct      s_container
{
    t_philo         *all_philos;
    t_fork          *all_forks;
    int             number_of_meals;
    long            number_of_philos;
    long            time_to_eat;
    long            time_to_die;
    long            time_to_sleep;
}                   t_container;

void ft_error(char *err);
void is_argument_has_number(char *str);
long is_valid_numbers(char *str);
void parse_content(t_container *content, char **av);
int	ft_isdigit(int c);
size_t	ft_strlen(const char *s);
long	long_ft_atoi(const char *str);
void create_philos(t_container *content);
t_philo *ft_lstnew_philo(int philo_number);
t_fork *ft_lstnew_fork(int philo_number);
void	ft_lstadd_back_philo(t_philo **lst, t_philo *new);
void	ft_lstadd_back_fork(t_fork **lst, t_fork *new);
void assign_forks_to_philo(t_container *content);


#endif