
#include "philo.h"

void argument_parsing(t_container *content, char **av)
{
    parse_content(content, av);
    create_philos(content);
    assign_forks_to_philo(content);
    start_actions(content);
    // while (content->all_philos)
    // {
    //     printf("philo(%d) , left (%d) right (%d)\n", content->all_philos->id, content->all_philos->left_fork->fork_id, content->all_philos->right_fork->fork_id);
    //     content->all_philos = content->all_philos->next;
    // }
}

int main(int ac, char **av)
{
    t_container content;

    if (ac < 5 || ac > 6)
        ft_error("Invalid number of arguments!");
    argument_parsing(&content, av);
    // printf("%zu\n", content.number_of_philos);
    // printf("%d\n", content.number_of_meals);
    // printf("%zu\n", content.time_to_die);
    // printf("%zu\n", content.time_to_eat);
    // printf("%zu\n", content.time_to_sleep);

    // data_initialzing();
    return (0);
}