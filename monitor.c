/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 01:22:25 by mmariani          #+#    #+#             */
/*   Updated: 2023/02/15 04:38:48 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	philokill(t_input *input)
{
	pthread_mutex_lock(&input->die_mutex);
	input->some_die = 0;
	pthread_mutex_unlock(&input->die_mutex);
}

static int	havealleat(t_input *input, int *howmanyphilo)
{
	if (*howmanyphilo >= input->n_ph)
	{
		philokill(input);
		input->havealleat = 0;
		return (1);
	}
	else
		*howmanyphilo = 0;
	return (0);
}

static void	print_die(t_philo *ph, int id, char *str)
{
	pthread_mutex_lock(&ph->input->lock);
	printf("%llu", ft_get_time() - ph->input->start_time);
	printf(" %d %s\n", id, str);
}

void	ft_monitor(t_input *input, int i, long long tmp)
{
	t_philo		*philo;
	int			howmanyphilo;

	philo = input->philo;
	while (1)
	{
		while (++i < input->n_ph)
		{
			pthread_mutex_lock(&input->philo_time);
			tmp = ft_get_time() - input->start_time - philo[i].t_starteating;
			pthread_mutex_unlock(&input->philo_time);
			if (tmp > (long long) input->tt_die)
			{
				philokill(input);
				print_die(&philo[i], philo[i].id, "is died");
				return ;
			}
			if (ft_check_mutex(1, &philo[i]))
				howmanyphilo++;
		}
		if (havealleat(input, &howmanyphilo))
			return ;
		i = -1;
	}
}
