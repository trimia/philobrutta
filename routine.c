/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 01:18:16 by mmariani          #+#    #+#             */
/*   Updated: 2023/02/15 04:15:08 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	timestarteating(t_philo *philo)
{
	pthread_mutex_lock(&philo->input->philo_time);
	philo->t_starteating = ft_get_time() - philo->input->start_time;
	pthread_mutex_unlock(&philo->input->philo_time);
}

void	*ft_routine(void *phil)
{
	t_philo	*philo;

	philo = phil;
	if (philo->id % 2 == 0)
		ft_my_sleep(60);
	while (ft_check_mutex(0, philo))
	{	
		if (ft_take_forks(philo))
			return (NULL);
		timestarteating(philo);
		if (ft_check_mutex(0, philo))
		{
			ft_philo_msg(philo, philo->id, "is eating");
			ft_my_sleep(philo->input->tt_eat);
		}
		philo->n_eat++;
		if (philo->n_eat == philo->input->n_to_eat)
		{
			pthread_mutex_lock(&philo->input->eat_mutex);
			philo->end = 1;
			pthread_mutex_unlock(&philo->input->eat_mutex);
		}
		ft_action(philo);
	}
	return (NULL);
}
