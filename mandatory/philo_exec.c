#include "philo.h"

long get_time()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
    {
        //shoud free
        ft_error("Error in time");
    }
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void *philo_actions(void *args)
{
    t_philo *philo;

    philo = (t_philo*)args;
    // printf("philo -> (%d) (%ldsm)\n", philo->id, get_time());
    printf("%ld %d is thinking\n", get_time(), philo->id);
    return (NULL);
}

void start_actions(t_container *content)
{
    t_philo *philo;
    philo = content->all_philos;
    while (philo)
    {
        if (pthread_create(&philo->thread, NULL, &philo_actions, philo) != 0)
        {
            // free
            ft_error("Error in threads!");
        }
        philo = philo->next;
    }
    philo = content->all_philos;
    while (philo)
    {
        if (pthread_join(philo->thread, NULL) != 0)
        {
            // free
            ft_error("Error in join for threads!");
        }
        philo = philo->next;
    }
}