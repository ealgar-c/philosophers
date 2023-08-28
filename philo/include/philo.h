/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:43:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/25 16:53:24 by ealgar-c         ###   ########.fr       */
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
# include <stdbool.h>

struct	s_master;

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

//checker.c
bool	ft_isdigit(int c);
bool	valid_atoi(char *str);
bool	check_args(int ac, char **av);
void	bad_args(void);

// time.c
long	get_actual_time(void);
long	process_timer(t_philo *philo);
void	ft_usleep(int time);

//initialize.c
void	init_academy(t_master *academy, int ac, char **av);
void	init_forks(t_master *academy);
void	init_philos(t_master *academy);

// states.c
void	print_state(t_philo *philo, int state);
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);

// routine.c
bool	finished_meal(t_master *academy);
void	*ft_philo(void *philo_tocast);
void	crt_routines(t_master *academy);
void	clr_routines(t_master *academy);

// main.c
int		ft_atoi(const char *str);

#endif