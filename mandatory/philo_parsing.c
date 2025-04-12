#include "philo.h"

void ft_error(char *err)
{
    printf("%s\n", err);
    exit(EXIT_FAILURE);
}

void is_argument_has_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            return ;
        i++;
    }
    ft_error("An arguments not numeric");
}

long is_valid_numbers(char *str)
{
    long    p_nb;

    if (!str || str[0] == '\0')
        ft_error("Number of philosophers not valid!");
    is_argument_has_number(str);
    if (ft_strlen(str) > 10)
        ft_error("Arguments number is more that int max");
    p_nb = long_ft_atoi(str);
    if (p_nb == 0)
        ft_error("Number must be bigger than 0");
    if (p_nb > INT_MAX)
        ft_error("Arguments number is more that int max");
    if (p_nb < 0)
        ft_error("All number must be posivite");
    return (p_nb);
}

void parse_content(t_container *content, char **av)
{
    content->all_forks = NULL;
    content->all_philos = NULL;
    content->number_of_philos = is_valid_numbers(av[1]);
    content->time_to_die = is_valid_numbers(av[2]);
    content->time_to_eat = is_valid_numbers(av[3]);
    content->time_to_sleep = is_valid_numbers(av[4]);
    if (av[5])
        content->number_of_meals = (int)is_valid_numbers(av[5]);
    else
        content->number_of_meals = -1;
}