/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:11:59 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/20 21:58:44 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

# define FORKS "/forks"
# define DEAD "/dead"
# define PRINT "/print"

typedef struct      s_container
{
    struct s_philo  *all_philos;
    sem_t           *fork;
    sem_t           *dead;
    sem_t           *print;
    int             number_of_meals;
    int             is_die;
    long            number_of_philos;
    long            time_to_eat;
    long            time_to_die;
    long            time_to_sleep;
    long            started_time;
}                   t_container;

typedef struct      s_philo
{
    int             id;
    pthread_t       monitor;
    pid_t           process;
    int             meals;
    long            time_last_meal;
    sem_t           *last_meal;
    char            *last_meal_name;
    sem_t           *p_meals;
    char            *p_meals_name;
    t_container     *content;
    struct          s_philo *next;
}                   t_philo;

void    ft_error(char *err);
int     is_argument_has_number(char *str);
int     is_valid_numbers(char *str, long *p_nb);
int	    ft_isdigit(int c);
size_t	ft_strlen(const char *s);
long	long_ft_atoi(const char *str);
long    get_time(void);
void    *check_for_deaths(void *data);
char	*ft_strjoin(char *s1, char *s2);
int     ft_sleep(long time, t_container *content);
int     parse_content(t_container *content, char **av);
void    create_philos(t_container *content);
int     assign_forks_to_philo(t_container *content);
char	*ft_itoa(int n);
int     start_philo_action(t_container *content);
void    *check_for_deaths(void *data);
int     philo_actions(t_philo *philo);
long    get_time();
void     check_and_print(t_philo *philo, t_container *content, char *message);
int     ft_wait(t_container *content, t_philo *philo, int flag);
void    ft_put_forks(t_container *content);
int     ft_philo_eating(t_philo *philo, t_container *content);
int     ft_philo_thinking(t_philo *philo, t_container *content);
int     ft_philo_die(t_container *content);
int     ft_take_forks(t_philo *philo, t_container *content);
int     ft_philo_sleeping(t_philo *philo, t_container *content);
void    clean_res(t_container *content);
void    ft_kill(t_container *content);
void    clean_philo(t_philo *philo);

#endif