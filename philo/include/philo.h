/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:43:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/18 17:05:57 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>

typedef struct s_philo{
	int				index;
	struct timeval	last_meal_ts;
	int				nb_of_meals;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_fork{
	int				index;
	pthread_mutex_t	thread;
}	t_fork;

typedef struct s_master{
	int					number_of_philos;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	struct timeval		init_ts;
	int					nb_of_meals;
	int					temp_nbr;
	int					actual_group;
	t_philo				*philos;
	t_fork				*forks;
}	t_master;

#endif