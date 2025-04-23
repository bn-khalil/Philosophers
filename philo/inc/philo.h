/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:25:20 by bn-khalil         #+#    #+#             */
/*   Updated: 2025/04/23 15:54:04 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_fork
{
	int				fork_id;
	struct s_fork	*next;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_container
{
	int				number_of_meals;
	int				is_die;
	int				all_finish;
	long			number_of_philos;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	long			started_time;
	t_fork			*all_forks;
	pthread_t		thread_monitor;
	struct s_philo	*all_philos;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
}	t_container;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			time_last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	t_container		*content;
	struct s_philo	*next;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	p_meals;
}	t_philo;

void	ft_error(char *err);
int		parse_content(t_container *content, char **av);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
long	long_ft_atoi(const char *str);
void	create_philos(t_container *content);
int		assign_forks_to_philo(t_container *content);
int		start_actions(t_container *content);
long	get_time(void);
char	*ft_strjoin(char *s1, char *s2);
int		ft_philo_die(t_philo *philo);
int		ft_take_forks(t_philo *philo);
int		ft_philo_eating(t_philo *philo);
int		check_and_print(t_philo *philo, char *message);
int		ft_sleep(long time, t_container *content);
int		ft_philo_sleeping(t_philo *philo);
int		ft_philo_thinking(t_philo *philo);
int		ft_wait(t_container *content, t_philo *philo, int flag);
void	ft_put_forks(t_philo *philo);
void	*action_one(void *data);

#endif