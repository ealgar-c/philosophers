/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:43:19 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/06 15:05:36 by ealgar-c         ###   ########.fr       */
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
		pthread_mutex_lock(&academy->dr_mutexes->eating);
		if (academy->arr_philos[i].nb_of_meals < academy->nb_of_meals)
		{
			pthread_mutex_unlock(&academy->dr_mutexes->eating);
			return (false);
		}
		pthread_mutex_unlock(&academy->dr_mutexes->eating);
		i++;
	}
	pthread_mutex_unlock(&academy->dr_mutexes->eating);
	return (true);
}

void	*check_death(void *philo_tocast)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tocast;
	while (1)
	{
		pthread_mutex_lock(&philo->academy->dr_mutexes->dead);
		if (finished_meal(philo->academy))
			break ;
		if (get_actual_time() - philo->last_meal > philo->academy->time_to_die)
		{
			print_state(philo, 3);
			pthread_mutex_lock(&philo->academy->dr_mutexes->print);
			philo->academy->ph_dead = true;
			pthread_mutex_unlock(&philo->academy->dr_mutexes->dead);
			pthread_mutex_unlock(&philo->academy->dr_mutexes->print);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->academy->dr_mutexes->dead);
	}
	return (NULL);
}

void	*ft_philo(void *philo_tocast)
{
	t_philo		*philo;
	pthread_t	check_death_thread;

	philo = (t_philo *)philo_tocast;
	philo->last_meal = get_actual_time();
	pthread_create(&check_death_thread, NULL, check_death, philo);
	if (philo->index % 2 == 0)
		usleep(1);
	while (!finished_meal(philo->academy))
	{
		//podria intentar reducir esto haciendo una funcion por aqui to guapa
		pthread_mutex_lock(&philo->academy->dr_mutexes->print);
		if (!philo->academy->ph_dead)
		{			
			pthread_mutex_unlock(&philo->academy->dr_mutexes->print);
			thinking(philo);
			eating(philo);
			sleeping(philo);
		}
		else
		{
		
			pthread_mutex_unlock(&philo->academy->dr_mutexes->print);
			break ;
		}
	}
	//pthread_mutex_unlock(&philo->academy->dr_mutexes->print); (con el 5 800 200 200 7, cuando se termina de comer el programa sigue esperando a algo)
	pthread_join(check_death_thread, NULL);
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
	pthread_mutex_destroy(&academy->dr_mutexes->eating);
	pthread_mutex_destroy(&academy->dr_mutexes->dead);
	pthread_mutex_destroy(&academy->dr_mutexes->print);
	free(academy->arr_forks);
	free(academy->arr_philos);
	free(academy->arr_threads);
}
