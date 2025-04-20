/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:12 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/20 14:55:38 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int  argument_parse_init(t_container *content, char **av)
{
    if (!content)
        return (1);
    if (parse_content(content, av))
        return (1);
    if (start_philo_action(content))
        return (1);
    return (0);
}

int main(int ac, char **av)
{
    t_container content;
    
    if (ac < 5 || ac > 6)
    {
        ft_error("Invalid number of arguments!");
        return (1);   
    }
    if (argument_parse_init(&content, av))
        return (1);
    return (0);
}
