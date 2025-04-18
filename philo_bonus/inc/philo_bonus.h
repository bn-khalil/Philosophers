/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:35:21 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/18 18:55:25 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <limits.h>
# include <sys/time.h>

# define FORKS "/fork"
# define DEAD "/dead"
# define PRINT "/print"

typedef struct      s_fork
{
    int             fork_id;
    char            *fork_name;
    sem_t           *fork;
    struct          s_fork *next;
}                   t_fork;

typedef struct      s_container
{
    struct s_philo  *all_philos;
    t_fork          *all_forks;
    int             number_of_meals;
    int             is_die;
    long            number_of_philos;
    long            time_to_eat;
    long            time_to_die;
    long            time_to_sleep;
    long            started_time;
    sem_t           *dead;
    char            *dead_name;
    sem_t           *print;
    char            *print_name;
    pthread_t       thread_monitor;
}                   t_container;

typedef struct      s_philo
{
    int             id;
    pid_t           process;
    sem_t           *last_meal;
    char            *last_meal_name;
    long            *time_last_meal;
    sem_t           *p_meals;
    char            *p_meals_name;
    int             meals;
    t_fork          *left_fork;
    t_fork          *right_fork;
    t_container     *content;
    struct          s_philo *next;
}                   t_philo;

void    ft_error(char *err);
int     is_argument_has_number(char *str);
int     is_valid_numbers(char *str, long *p_nb);
int	    ft_isdigit(int c);
size_t	ft_strlen(const char *s);
long	long_ft_atoi(const char *str);
t_philo *ft_lstnew_philo(int philo_number);
t_fork  *ft_lstnew_fork(int philo_number);
long    get_time(void);
void    *check_for_deaths(void *data);
char	*ft_strjoin(char *s1, char *s2);
int     ft_sleep(long time, t_container *content);
int     parse_content(t_container *content, char **av);
void    create_philos(t_container *content);
int     assign_forks_to_philo(t_container *content);
char	*ft_itoa(int n);

#endif