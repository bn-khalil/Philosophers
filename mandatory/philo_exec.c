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
    t_philo *philo = (t_philo*)args;
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->id % 2)
        usleep(500);
    while (!philo->content->is_die)
    {
        if (philo->content->number_of_meals != -1 && philo->meals >= philo->content->number_of_meals)
            return (NULL);
        if (philo->left_fork->fork_id < philo->right_fork->fork_id)
        {
            first_fork = &philo->left_fork->fork;
            second_fork = &philo->right_fork->fork;
        }
        else
        {
            first_fork = &philo->right_fork->fork;
            second_fork = &philo->left_fork->fork;
        }
        pthread_mutex_lock(first_fork);
        printf("%ld %d has taken left fork\n", get_time() - philo->content->started_time, philo->id);
        pthread_mutex_lock(second_fork);
        printf("%ld %d has taken right fork\n", get_time() - philo->content->started_time, philo->id);
        philo->time_last_meal = get_time() - philo->content->started_time;
        printf("%ld %d is eating\n", get_time() - philo->content->started_time, philo->id);
        ft_sleep(philo->content->time_to_eat);
        philo->meals++;
        pthread_mutex_unlock(first_fork);
        pthread_mutex_unlock(second_fork);
    
        printf("%ld %d is sleeping\n", get_time() - philo->content->started_time, philo->id);
        ft_sleep(philo->content->time_to_sleep);

        printf("%ld %d is thinking\n", get_time() - philo->content->started_time, philo->id);
    }
    return (NULL);
}

void only_one_phlio(t_container *content)
{
    printf("%ld %d has taken left fork\n", get_time() - content->started_time, content->all_philos->id);
    printf("%ld %d is thinking\n", get_time() - content->started_time, content->all_philos->id);
    ft_sleep(content->time_to_die);
    printf("%ld %d is die\n", get_time() - content->started_time, content->all_philos->id);
}

void *check_for_deads_o(void *data)
{
    t_container *content = (t_container *)data;
    t_philo *philo = content->all_philos;

    while (1)
    {
        philo = content->all_philos;
        while (philo)
        {
            // printf("(%ld)\n", content->time_to_die);
            // printf("(%ld)\n", philo->time_last_meal);
            if ((get_time() - content->started_time) - philo->time_last_meal > content->time_to_die)
            {
                philo->content->is_die = 1;
                printf("%ld %d died\n", get_time() - content->started_time, philo->id);
                return (NULL);
            }
            if (philo->content->is_die)
                return (NULL);
            philo = philo->next;
        }
        usleep(1000);
    }
    return (NULL);
}

void start_actions(t_container *content)
{
    t_philo *philo = content->all_philos;

    if (!philo)
        return ;
    content->started_time = get_time();
    if (!philo->next)
    {
        only_one_phlio(content);
        return ;
    }
    while (philo)
    {
        philo->content = content;
        if (pthread_create(&philo->thread, NULL, &philo_actions, philo) != 0)
            ft_error("Error in threads!");
        philo = philo->next;
    }
    if (pthread_create(&content->thread_monitor, NULL, &check_for_deads_o, content) != 0)
        ft_error("Error in threads!");
    if (pthread_join(content->thread_monitor, NULL) != 0)
        ft_error("Error in join for threads!");

    philo = content->all_philos;
    while (philo && !content->is_die)
    {
        if (pthread_join(philo->thread, NULL) != 0)
        {
            ft_error("Error in join for threads!");
        }
        philo = philo->next;
    }
}
