/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:43:19 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/21 12:43:32 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	finished_meal(t_master *academy)
{
	int	i;

	i = 0;
	if (academy->nb_of_meals == -1)
		return (false);
	while (i < academy->number_of_philos)
	{
		if (academy->arr_philos[i].nb_of_meals < academy->nb_of_meals)
			return (false);
		i++;
	}
	return (true);
}

void	*ft_philo(void *philo_tocast)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tocast;
	while (!philo->academy->ph_dead && !finished_meal(philo->academy))
	{
		if (get_actual_time() - philo->last_meal > philo->academy->time_to_die)
		{
			print_state(philo, 3);
			philo->academy->ph_dead = true;
			return (NULL);
		}
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
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
		pthread_create(&academy->arr_threads[i], NULL, ft_philo,
			&academy->arr_philos[i]);
		i++;
	}
	i = 0;
	while (i < academy->number_of_philos)
	{
		pthread_join(academy->arr_threads[i], NULL);
		i++;
	}
}

void	clr_routines(t_master *academy)
{
	int	i;

	i = 0;
	while (i < academy->number_of_philos)
	{
		pthread_mutex_destroy(&academy->arr_forks[i]);
		i++;
	}
	free(academy->arr_forks);
	free(academy->arr_philos);
	free(academy->arr_threads);
}
