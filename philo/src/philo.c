/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:10:12 by kben-tou          #+#    #+#             */
/*   Updated: 2025/04/16 14:31:53 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philo.h"

void argument_parse_init(t_container *content, char **av)
{
    if (!content)
        return ;
    if (parse_content(content, av));
        return ;
    create_philos(content);
    if (!content->all_forks || !content->all_philos)
        return ;
    assign_forks_to_philo(content);
    start_actions(content);
}

int main(int ac, char **av)
{
    t_container content;

    if (ac < 5 || ac > 6)
        ft_error("Invalid number of arguments!");
    argument_parse_init(&content, av);
    ft_free_all(&content);
    return (0);
}   