
#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

long	long_ft_atoi(const char *str)
{
	int		i;
	long	store;
	int		si;

	i = 0;
	si = 1;
	store = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			si *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		store = store * 10 + (str[i++] - '0');
	return (store * si);
}

void ft_error(char *err)
{
    printf("%s\n", err);
    exit(EXIT_FAILURE);
}
// philoNumbers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
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
    content->number_of_philos = is_valid_numbers(av[1]);
    content->time_to_die = is_valid_numbers(av[2]);
    content->time_to_eat = is_valid_numbers(av[3]);
    content->time_to_sleep = is_valid_numbers(av[4]);
    if (av[5])
        content->number_of_meals = (int)is_valid_numbers(av[5]);
    else
        content->number_of_meals = INT_MIN;
}


void create_philos(t_container *content)
{
    int         i;

    i = 0;
    if (!content)
        return ;
    content->all_philos = malloc(sizeof(t_philo) * content->number_of_philos);
    if (!content->all_philos)
        ft_error("Error create philosopher");
    content->all_forks = malloc(sizeof(t_fork) * content->number_of_philos);
    if (!content->all_forks)
        ft_error("Error create forks");
    while (i < content->number_of_philos)
    {
        content->all_forks[i].id = i;
        content->all_forks[i].meals = 0;
        content->all_forks[i].;
        i++;
    }

}

void argument_parsing(t_container *content, char **av)
{
    parse_content(content, av);
    philo_init(content);
    // is_argument_numbers();
}

int main(int ac, char **av)
{
    t_container content;

    if (ac < 5 || ac > 6)
        ft_error("Invalid number of arguments!");
    argument_parsing(&content, av);
    printf("%zu\n", content.number_of_philos);
    printf("%d\n", content.number_of_meals);
    printf("%zu\n", content.time_to_die);
    printf("%zu\n", content.time_to_eat);
    printf("%zu\n", content.time_to_sleep);

    // data_initialzing();
    return (0);
}