/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:07 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/20 16:53:22 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void ft_error(char *err)
{
    printf("%s\n", err);
}

int  is_argument_has_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '+' && str[i] != '-')
        {
            ft_error("Some or all arguments not numeric");
            return (1);
        }
        if ((str[i] == '+' || str[i] == '-') && !ft_isdigit(str[i + 1]))
        {
            ft_error("Some or all arguments not numeric");
            return (1);
        }
        i++;
    }
    return (0);
}

int is_valid_numbers(char *str, long *p_nb)
{
    if (!str || str[0] == '\0')
    {
        ft_error("Number of philosophers not valid!");
        return (1);
    }
    if (is_argument_has_number(str))
        return (1);
    if (ft_strlen(str) > 10)
    {
        ft_error("Arguments number is more than int max");
        return (1);
    }
    *p_nb = long_ft_atoi(str);
    if (*p_nb == 0)
    {
        ft_error("Number must be bigger than 0");
        return (1);
    }
    if (*p_nb > INT_MAX)
    {
        ft_error("Arguments number is more than int max");
        return (1);
    }
    if (*p_nb < 0)
    {
        ft_error("All numbers must be positive");
        return (1);
    }
    return (0);
}

int init_content(t_container *content)
{
    sem_unlink(DEAD);
    content->dead = sem_open(DEAD, O_CREAT, 0644, 1);
    if (content->dead == SEM_FAILED)
        return (1);
    sem_unlink(PRINT);
    content->print = sem_open(PRINT, O_CREAT, 0644, 1);
    if (content->print == SEM_FAILED)
    {
        sem_close(content->dead);
        sem_unlink(DEAD);
        return (1);
    }
    sem_unlink(FORKS);
    content->fork = sem_open(FORKS, O_CREAT, 0644, content->number_of_philos);
    if (content->fork == SEM_FAILED)
    {
        sem_close(content->dead);
        sem_unlink(DEAD);
        sem_close(content->print);
        sem_unlink(PRINT);
        return (1);
    }
    return (0);
}

int parse_content(t_container *content, char **av)
{
    long hold_number;

    hold_number = 0;
    content->all_philos = NULL;
    content->is_die = 0;
    content->started_time = 0;
    if (is_valid_numbers(av[1], &hold_number))
        return (1);
    content->number_of_philos = hold_number;
    if (is_valid_numbers(av[2], &hold_number))
        return (1);
    content->time_to_die = hold_number;
    if (is_valid_numbers(av[3], &hold_number))
        return (1);
    content->time_to_eat = hold_number;
    if (is_valid_numbers(av[4], &hold_number))
        return (1);
    content->time_to_sleep = hold_number;
    if (av[5])
    {
        if (is_valid_numbers(av[5], &hold_number))
            return (1);
        content->number_of_meals = (int)hold_number;
    }
    else
        content->number_of_meals = -1;
    if (init_content(content))
        return (1);
    return (0);
}
