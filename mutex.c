/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:13:01 by mmariani          #+#    #+#             */
/*   Updated: 2023/02/15 04:15:47 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_initmutex(t_input *input)
{
	int	i;

	i = 0;
	pthread_mutex_init(&input->die_mutex, NULL);
	pthread_mutex_init(&input->lock, NULL);
	pthread_mutex_init(&input->eat_mutex, NULL);
	pthread_mutex_init(&input->philo_time, NULL);
	input->forks = (pthread_mutex_t *) malloc
		(sizeof(pthread_mutex_t) * input->n_ph);
	if (!input->forks)
		return (-1);
	while (i < input->n_ph)
		pthread_mutex_init(&input->forks[i++], NULL);
	return (0);
}

int	ft_check_mutex(int flag, t_philo *philo)
{
	int	tmp;

	tmp = 0;
	if (flag == 0)
	{
		pthread_mutex_lock(&philo->input->die_mutex);
		tmp = philo->input->some_die;
		pthread_mutex_unlock(&philo->input->die_mutex);
	}
	else if (flag == 1)
	{
		pthread_mutex_lock(&philo->input->eat_mutex);
		tmp = philo->end;
		pthread_mutex_unlock(&philo->input->eat_mutex);
	}
	return (tmp);
}
