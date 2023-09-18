/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:42:48 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/08 15:27:59 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	print_state(t_philo *philo, int state)
{
	if (state == 0)
		printf("%ld %d is eating\n", process_timer(philo), philo->index);
	else if (state == 1)
		printf("%ld %d is thinking\n", process_timer(philo), philo->index);
	else if (state == 2)
		printf("%ld %d is sleeping\n", process_timer(philo), philo->index);
	else if (state == 3)
		printf("%ld %d died\n", process_timer(philo), philo->index);
	else if (state == 4)
		printf("%ld %d has taken a fork\n",
			process_timer(philo), philo->index);
	else
		return ;
}

void	thinking(t_philo *philo)
{
	print_state(philo, 1);
}

void	eating(t_philo *philo)
{
	if (finished_meal(philo))
		return ;
	sem_wait(philo->academy->forks);
	print_state(philo, 4);
	sem_wait(philo->academy->forks);
	print_state(philo, 4);
	print_state(philo, 0);
	pthread_mutex_lock(&philo->academy->dr_mutexes->upd_time);
	philo->last_meal = get_actual_time();
	pthread_mutex_unlock(&philo->academy->dr_mutexes->upd_time);
	usleep(philo->academy->time_to_eat * 1000);
	pthread_mutex_lock(&philo->academy->dr_mutexes->eating);
	philo->nb_of_meals++;
	pthread_mutex_unlock(&philo->academy->dr_mutexes->eating);
	sem_post(philo->academy->forks);
	sem_post(philo->academy->forks);
}

void	sleeping(t_philo *philo)
{
	print_state(philo, 2);
	usleep(philo->academy->time_to_sleep * 1000);
}
