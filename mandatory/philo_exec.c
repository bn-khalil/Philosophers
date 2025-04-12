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

void ft_sleep(long time)
{
    long te;

    te = get_time();
    while ((get_time() - te) < time)
        usleep(1000);
}

void *philo_actions(void *args)
{
    t_philo *philo;

    philo = (t_philo*)args;
    if (philo->id % 2 == 0)
        usleep(1000);
    while (philo->status != P_DIE)
    {
        if (philo->content->number_of_meals != -1 && philo->meals >= philo->content->number_of_meals)
            break ;

        pthread_mutex_lock(&philo->left_fork->fork);
        printf("%ld %d has taken left fork\n", get_time(), philo->id);
        pthread_mutex_lock(&philo->right_fork->fork);
        printf("%ld %d has taken right fork\n", get_time(), philo->id);

        philo->status = P_EAT;
        philo->time_last_meal = get_time();
        printf("%ld %d is eating\n", philo->time_last_meal, philo->id);
        ft_sleep(philo->content->time_to_eat);
        philo->meals++;
        pthread_mutex_unlock(&philo->left_fork->fork);
        pthread_mutex_unlock(&philo->right_fork->fork);
    
        philo->status = P_SLEEP;
        printf("%ld %d is sleeping\n", get_time(), philo->id);
        ft_sleep(philo->content->time_to_sleep);

        philo->status = P_THINK;
        printf("%ld %d is thinking\n", get_time(), philo->id);
        // usleep(philo->content->time_to_sleep * 1000);
    }
    return (NULL);
}

void start_actions(t_container *content)
{
    t_philo *philo;
    philo = content->all_philos;
    while (philo)
    {
        philo->content = content;
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