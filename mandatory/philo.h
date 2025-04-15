/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:35:21 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/15 16:59:45 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct      s_fork
{
    int             fork_id;
    pthread_mutex_t fork;
    struct          s_fork *next;
}                   t_fork;


typedef struct      s_container
{
    struct   s_philo         *all_philos;
    t_fork          *all_forks;
    int             number_of_meals;
    int             is_die;
    long            number_of_philos;
    long            time_to_eat;
    long            time_to_die;
    long            time_to_sleep;
    long            started_time;
    pthread_mutex_t dead;
    pthread_t       thread_monitor;
}                   t_container;

typedef struct      s_philo
{
    int             id;
    pthread_t       thread;
    long            time_last_meal;
    pthread_mutex_t last_meal;
    pthread_mutex_t p_meals;
    t_fork          *left_fork;
    t_fork          *right_fork;
    int             meals;
    t_container     *content;
    struct          s_philo *next;
}                   t_philo;


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
void start_actions(t_container *content);
long get_time(void);
// void check_for_deads(t_container *content);
void ft_free_all(t_container *content);


#endif