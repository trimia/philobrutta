/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 01:37:09 by mmariani          #+#    #+#             */
/*   Updated: 2023/02/15 04:15:20 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (ft_check_mutex(0, philo))
		ft_philo_msg(philo, philo->id, "has taken a fork");
	if (philo->input->n_ph == 1)
		return (1);
	pthread_mutex_lock(philo->right);
	if (ft_check_mutex(0, philo))
		ft_philo_msg(philo, philo->id, "has taken a fork");
	return (0);
}

void	ft_action(t_philo *philo)
{
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	if (ft_check_mutex(0, philo))
		ft_philo_msg(philo, philo->id, "is sleeping");
	if (ft_check_mutex(0, philo))
		ft_my_sleep(philo->input->tt_sleep);
	if (ft_check_mutex(0, philo))
		ft_philo_msg(philo, philo->id, "is thinking");
}
