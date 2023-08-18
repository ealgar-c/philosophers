/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:43:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/18 17:28:14 by ealgar-c         ###   ########.fr       */
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

struct s_master;

typedef struct s_philo{
	int				index;
	long			last_meal;
	int				nb_of_meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_master	*academy;
}	t_philo;

typedef struct s_master{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_meals;
	long				init_time;
	bool				ph_dead;
	pthread_t			*arr_threads;
	t_philo				*arr_philos;
	pthread_mutex_t		*arr_forks;
}	t_master;

#endif