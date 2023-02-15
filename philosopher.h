/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:54:15 by mmariani          #+#    #+#             */
/*   Updated: 2023/02/15 01:00:16 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_input	*input;
	int				id;
	int				n_eat;
	int				end;
	uint64_t		strv;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	strv_mutex;

}				t_philo;

typedef struct s_input
{
	int				n_ph;
	uint64_t		tt_die;
	uint64_t		tt_eat;
	uint64_t		tt_sleep;
	int				n_to_eat;
	int				some_die;
	int				stillrunning;
	uint64_t		start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	philo_time;
	pthread_mutex_t	lock;
}	t_input;

int			ft_check(int argc, char **argv);
long long	ft_atoi(const char *str);
void		ft_my_sleep(uint64_t time);
void		ft_philo_msg(t_philo *ph, int id, char *str);
int			ft_initmutex(t_input *input);
uint64_t	ft_get_time(void);

#endif