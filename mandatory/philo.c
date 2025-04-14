
#include "philo.h"

// void *check_for_deads(void *data)
// {
//     t_philo *philo;

//     while (1)
//     {
//         philo = content->all_philos;
//         while (philo)
//         {
//             if (content->number_of_meals != -1 && philo->meals >= content->number_of_meals)
//                 return ;
//             if (get_time() - philo->time_last_meal > content->time_to_die)
//             {
//                 philo->content->is_die = 1;
//                 printf("%ld %d died\n", get_time() - content->started_time, philo->id);
//                 return ;
//             }
//             if (philo->content->is_die)
//                 return ;
//             philo = philo->next;
//         }
//         usleep(1000);
//     }
// }

void argument_parsing(t_container *content, char **av)
{
    parse_content(content, av);
    create_philos(content);
    assign_forks_to_philo(content);
    start_actions(content);
    ft_free_all(content);
}

int main(int ac, char **av)
{
    t_container content;

    if (ac < 5 || ac > 6)
        ft_error("Invalid number of arguments!");
    argument_parsing(&content, av);
    return (0);
}   