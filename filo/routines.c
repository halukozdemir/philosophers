#include "philo.h"

void print_action(t_philo *philo, const char *action) {
    pthread_mutex_lock(philo->write_lock);
    if (!(*philo->dead)) { // Bir filozof öldüğünde yazmayı durdur
        printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id, action);
    }
    pthread_mutex_unlock(philo->write_lock);
}

void take_forks(t_philo *philo) {
    if (philo->id % 2 == 0) {
        pthread_mutex_lock(philo->r_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->l_fork);
        print_action(philo, "has taken a fork");
    } else {
        pthread_mutex_lock(philo->l_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->r_fork);
        print_action(philo, "has taken a fork");
    }
}

void eat(t_philo *philo) {
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_current_time();
    pthread_mutex_unlock(philo->meal_lock);
    print_action(philo, "is eating");
    usleep(philo->time_to_eat * 1000);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}

void *philo_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    while (!(*philo->dead)) {
        print_action(philo, "is thinking");
        take_forks(philo);
        if (*philo->dead) break; // Bir filozof öldüğünde döngüden çık
        eat(philo);
        if (*philo->dead) break; // Bir filozof öldüğünde döngüden çık
        print_action(philo, "is sleeping");
        usleep(philo->time_to_sleep * 1000);
        if (*philo->dead) break; // Bir filozof öldüğünde döngüden çık
    }
    return NULL;
}

void *monitor_routine(void *arg) {
    t_program *prog = (t_program *)arg;
    int i;

    while (!prog->dead_flag) {
        i = 0;
        while (i < prog->num_of_philos) {
            pthread_mutex_lock(&prog->meal_lock);
            if (get_current_time() - prog->philos[i].last_meal > prog->philos[i].time_to_die) {
                pthread_mutex_lock(&prog->write_lock);
                printf("%zu %d died\n", get_current_time() - prog->philos[i].start_time, prog->philos[i].id);
                prog->dead_flag = 1;
                pthread_mutex_unlock(&prog->write_lock);
                pthread_mutex_unlock(&prog->meal_lock);
                return NULL; // Bir filozof öldüğünde monitor thread'i döngüden çık
            }
            pthread_mutex_unlock(&prog->meal_lock);
            i++;
        }
        usleep(1000);
    }
    return NULL;
}
