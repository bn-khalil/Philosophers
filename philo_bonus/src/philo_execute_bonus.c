#include "../inc/philo_bonus.h"

void ft_kill(t_container *content)
{
    int i = 0;
    while (i < content->number_of_philos)
    {
        if (content->pid[i] > 0)
            kill(content->pid[i], SIGKILL);
        i++;
    }
}

int philo_actions(t_container *content, int i)
{
    if (i % 2 == 0)
        usleep(500);
    while (1)
    {
        sem_wait(content->fork);
        printf("%ld %d has taken a fork\n", get_time() - content->started_time, i);
        sem_wait(content->fork);
        printf("%ld %d has taken a fork\n", get_time() - content->started_time, i);
        sem_wait(content->last_meal);
        content->time_last_meal = get_time();
        sem_post(content->last_meal);
        printf("%ld %d is eating \n", get_time() - content->started_time, i);
        ft_sleep(content->time_to_eat, content);
        content->meals++;
        sem_post(content->fork);
        sem_post(content->fork);
        printf("%ld %d is sleeping \n", get_time() - content->started_time, i);
        ft_sleep(content->time_to_sleep, content);
        printf("%ld %d is thinking \n", get_time() - content->started_time, i);
    }
    return (0);
}

void *check_for_deaths(void *data)
{
    long spended_time;

    t_container *content = (t_container *)data;
    while (1)
    {
        sem_wait(content->last_meal);
        spended_time = get_time() - content->time_last_meal;
        sem_post(content->last_meal);
        if (spended_time > content->time_to_die)
        {
            sem_wait(content->print);
            printf("%ld died\n", get_time() - content->started_time);
            sem_post(content->print);
            exit(1);
        }
        usleep(1000);
    }
    return (NULL);
}

void prepare(t_container *content, int i)
{
    content->last_meal_name = ft_strjoin("meal_name_", ft_itoa(i));
    sem_unlink(content->last_meal_name);
	content->last_meal = sem_open(content->last_meal_name, O_CREAT, 0644, 1);
}

int start_philo_action(t_container *content)
{
    int i;
    int state;

    i = 0;
    state = 0;
    while (i < content->number_of_philos)
    {
        content->pid[i] = fork();
        if (content->pid[i] < 0)
            ft_error("fork");
        if (content->pid[i] == 0)
        {
            prepare(content, i);
            content->started_time = get_time();
            if (pthread_create(&content->monitor, NULL, &check_for_deaths, content) != 0)
                printf("error\n");
            pthread_detach(content->monitor);
            sem_wait(content->dead);
            content->time_last_meal = get_time();
            sem_post(content->dead);
            philo_actions(content, i);
            exit(0);
        }
        i++;
    }
    i = 0;
    while (i < content->number_of_meals)
    {
        while (waitpid(content->pid[i], &state, -1) > 0)
        {
            if (state != 0)
            {
                ft_kill(content);
                break ;
            }
        }
        i++;
    }
    
    return (0);
}
