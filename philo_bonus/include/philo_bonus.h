/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:43:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/07 15:57:54 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <semaphore.h>

struct	s_master;

typedef struct s_philo{
	int				index;
	int				pid;
	long			last_meal;
	int				nb_of_meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_master	*academy;
}	t_philo;

typedef struct s_dr{
	pthread_mutex_t	eating;
	pthread_mutex_t	die;
	pthread_mutex_t	upd_time;
}	t_dr;

typedef struct s_master{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_meals;
	long				init_time;
	bool				philodied;
	sem_t				*ph_dead;
	pthread_t			*arr_threads;
	t_philo				*arr_philos;
	sem_t				*forks;
	t_dr				*dr_mutexes;
}	t_master;

//checker.c
bool	ft_isdigit(int c);
bool	valid_atoi(char *str);
bool	check_args(int ac, char **av);
void	bad_args(void);

// time.c
long	get_actual_time(void);
long	process_timer(t_philo *philo);

//initialize.c
void	init_academy(t_master *academy, int ac, char **av);
void	init_semaphores(t_master *academy);
void	init_philos(t_master *academy);

// states.c
void	print_state(t_philo *philo, int state);
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);

// routine.c
bool	finished_meal(t_philo *philo);
void	ft_philo(t_philo *philo);
void	crt_routines(t_master *academy);

// bonus.c
void	kill_all(t_master *academy);
void	clr_routines(t_master *academy);

// main.c
int		ft_atoi(const char *str);

#endif