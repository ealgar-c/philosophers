/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:43:19 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/12 17:16:42 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

bool	finished_meal(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->academy->nb_of_meals == -1)
		return (false);
	if (philo->nb_of_meals == philo->academy->nb_of_meals)
		return (true);
	return (false);
}

void	*monitoring(void *philo_tocast)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tocast;
	while (1)
	{
		sem_wait(philo->academy->ph_dead);
		sem_post(philo->academy->ph_dead);
		pthread_mutex_lock(&philo->academy->dr_mutexes->die);
		philo->academy->philodied = true;
		pthread_mutex_unlock(&philo->academy->dr_mutexes->die);
		exit (0);
		return (NULL);
	}
}

void	*check_death(void *philo_tocast)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tocast;
	while (1)
	{
		pthread_mutex_lock(&philo->academy->dr_mutexes->upd_time);
		if (finished_meal(philo))
			break ;
		pthread_mutex_lock(&philo->academy->dr_mutexes->eating);
		if (get_actual_time() - philo->last_meal > philo->academy->time_to_die
			&& !philo->academy->philodied)
		{
			pthread_mutex_unlock(&philo->academy->dr_mutexes->upd_time);
			pthread_mutex_unlock(&philo->academy->dr_mutexes->eating);
			print_state(philo, 3);
			sem_post(philo->academy->ph_dead);
			exit(0);
		}
		pthread_mutex_unlock(&philo->academy->dr_mutexes->eating);
		pthread_mutex_unlock(&philo->academy->dr_mutexes->upd_time);
	}
	return (NULL);
}

void	ft_philo(t_philo *philo)
{
	pthread_t	monitoring_thread;
	pthread_t	check_death_thread;

	pthread_create(&monitoring_thread, NULL, monitoring, philo);
	pthread_create(&check_death_thread, NULL, check_death, philo);
	while (!finished_meal(philo))
	{
		pthread_mutex_lock(&philo->academy->dr_mutexes->die);
		if (philo->academy->philodied)
		{
			pthread_mutex_unlock(&philo->academy->dr_mutexes->die);
			break ;
		}
		pthread_mutex_unlock(&philo->academy->dr_mutexes->die);
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	exit(0);
}

void	crt_routines(t_master *academy)
{
	int	i;

	academy->init_time = get_actual_time();
	if (academy->number_of_philos == 1)
	{
		thinking(&academy->arr_philos[0]);
		usleep(academy->time_to_die * 1000);
		print_state(&academy->arr_philos[0], 3);
		return ;
	}
	i = 0;
	while (i < academy->number_of_philos)
	{
		academy->arr_philos[i].pid = fork();
		if (academy->arr_philos[i].pid == 0)
			ft_philo(&academy->arr_philos[i]);
		i++;
		usleep(100);
	}
	waitpid(-1, NULL, 0);
}
