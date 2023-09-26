/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:42:48 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/21 15:19:58 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->academy->dr_mutexes->print);
	if (philo->academy->ph_dead)
	{
		pthread_mutex_unlock(&philo->academy->dr_mutexes->print);
		return ;
	}
	else if (state == 0)
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
	pthread_mutex_unlock(&philo->academy->dr_mutexes->print);
}

void	thinking(t_philo *philo)
{
	print_state(philo, 1);
}

static void	take_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, 4);
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, 4);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, 4);
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, 4);
	}
}

void	eating(t_philo *philo)
{
	if (finished_meal(philo->academy))
		return ;
	take_forks(philo);
	print_state(philo, 0);
	pthread_mutex_lock(&philo->academy->dr_mutexes->dead);
	philo->last_meal = get_actual_time();
	pthread_mutex_unlock(&philo->academy->dr_mutexes->dead);
	ft_usleep(philo->academy->time_to_eat);
	pthread_mutex_lock(&philo->academy->dr_mutexes->eating);
	philo->nb_of_meals++;
	pthread_mutex_unlock(&philo->academy->dr_mutexes->eating);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_state(philo, 2);
	ft_usleep(philo->academy->time_to_sleep);
}
