/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:07 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/17 10:10:45 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
        ft_error("Arguments number is more that int max");
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
        ft_error("Arguments number is more that int max");
        return (1);
    }
    if (*p_nb < 0)
    {
        ft_error("All number must be posivite");
        return (1);
    }
    return (0);
}

int  parse_content(t_container *content, char **av)
{
    long hold_number;

    hold_number = 0;
    content->all_forks = NULL;
    content->all_philos = NULL;
    content->is_die = 0;
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
    if (pthread_mutex_init(&content->dead, NULL) != 0 \
    || pthread_mutex_init(&content->print, NULL) != 0)
    {
        ft_error("Failed to init mutex");
        return (1);
    }
    if (av[5])
    {
        if (is_valid_numbers(av[5], &hold_number))
            return (1);
        content->number_of_meals = (int)hold_number;
    }
    else
        content->number_of_meals = -1;
    return (0);
}
