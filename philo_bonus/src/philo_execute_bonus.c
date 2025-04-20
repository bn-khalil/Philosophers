#include "../inc/philo_bonus.h"

void ft_kill(t_container *content)
{
    t_philo *philo;

    philo = content->all_philos;
    while (philo)
    {
        if (philo->monitor)
            pthread_detach(philo->monitor);
        if (philo->process > 0)
            kill(philo->process, SIGKILL);
        philo = philo->next;
    }
    exit(0);
}

int philo_actions(t_philo *philo)
{
    t_container *content;

    content = philo->content;
    if (philo->id % 2 == 0)
        usleep(500);
    while (1)
    {
        sem_wait(content->fork);
        check_and_print(philo, content, "has taken a fork\n");
        sem_wait(content->fork);
        check_and_print(philo, content, "has taken a fork\n");
        sem_wait(philo->last_meal);
        philo->time_last_meal = get_time();
        sem_post(philo->last_meal);
        check_and_print(philo, content, "is eating\n");
        ft_sleep(content->time_to_eat, content);
        sem_wait(philo->p_meals);
        philo->meals++;
        sem_post(philo->p_meals);
        sem_post(content->fork);
        sem_post(content->fork);
        check_and_print(philo, content,"is sleeping\n");
        ft_sleep(philo->content->time_to_sleep, content);
        check_and_print(philo, content,"is thinking\n");
        if (content->number_of_meals != -1 && philo->meals >= content->number_of_meals)
            exit(0);
    }
    return (0);
}

void *check_for_deaths(void *data)
{
    t_philo *philo;
    int is_all_done;

    philo = (t_philo *)data;
    is_all_done = 0;
    while (1)
    {
        sem_wait(philo->last_meal);
        if (philo->content->time_to_die < get_time() - philo->time_last_meal)
        {
            sem_post(philo->last_meal);
            sem_wait(philo->content->print);
            printf("%ld %d %s", get_time() - philo->content->started_time, 
                   philo->id, "died\n");
            exit(1);
        }
        sem_wait(philo->p_meals);
        if (philo->content->number_of_meals != -1 && philo->meals >= philo->content->number_of_meals)
           is_all_done = 1;
        sem_post(philo->p_meals);
        if (philo->content->number_of_meals != -1 && is_all_done)
        {
            sem_post(philo->last_meal);
            exit(1);
        }
        sem_post(philo->last_meal);
        usleep(500);
    }
    return (NULL);
}

int start_philo_action(t_container *content)
{
    t_philo *philos;
    pid_t pid;
    int status;

    content->started_time = get_time();
    philos = content->all_philos;
    while (philos)
    {
        philos->content = content;
        philos->time_last_meal = content->started_time;
        philos->process = fork();
        if (philos->process < 0)
        {
            ft_error("Fork failed");
            ft_kill(content);
            return (1);
        }
        if (philos->process == 0)
        {
            if (pthread_create(&philos->monitor, NULL, check_for_deaths, philos) != 0)
                exit(1);
            if (pthread_detach(philos->monitor) != 0)
                exit(1);
            philo_actions(philos);
            exit(0);
        }
        philos = philos->next;
    }
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if (status != 0)
        {
            ft_kill(content);
            break;
        }
    }
    return (0);
}