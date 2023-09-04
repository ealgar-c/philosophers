/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:56:28 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/04 10:08:39 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	kill_all(t_master *academy)
{
	int	i;

	i = 0;
	while (i < academy->number_of_philos)
	{
		kill(academy->arr_philos[i].pid, SIGKILL);
		i++;
	}
}

void	clr_routines(t_master *academy)
{
	sem_unlink("forks");
	sem_close(academy->forks);
	sem_unlink("ph_dead");
	sem_close(academy->ph_dead);
	free(academy->arr_philos);
	free(academy->arr_threads);
	kill_all(academy);
}
