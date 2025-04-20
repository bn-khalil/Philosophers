/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:35:21 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/20 14:55:25 by kben-tou         ###   ########.fr       */
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
# include <fcntl.h>
# include <signal.h>

# define FORKS "/fork"
# define DEAD "/dead"
# define PRINT "/print"

// typedef struct      s_fork
// {
//     int             fork_id;
//     struct          s_fork *next;
// }                   t_fork;

typedef struct s_container
{
    pid_t           *pid;
	sem_t			*fork;
	sem_t			*dead;
	sem_t			*print;
	sem_t			*last_meal;
	char			*last_meal_name;
	pthread_t		monitor;
	int				meals;
	int				number_of_meals;
	long			number_of_philos;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	long			started_time;
	pthread_t		thread_monitor;
	long			time_last_meal;
}					t_container;

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
// int     philo_actions(t_philo *philo);
long    get_time();
// int     check_and_print(t_philo *philo, t_container *content, char *message);
// int     ft_wait(t_container *content, t_philo *philo, int flag);
void    ft_put_forks(t_container *content);
// int     ft_philo_eating(t_philo *philo, t_container *content);
// int     ft_philo_thinking(t_philo *philo, t_container *content);
// int     ft_philo_die(t_container *content);
// int     ft_take_forks(t_philo *philo, t_container *content);
// int     ft_philo_sleeping(t_philo *philo, t_container *content);

#endif