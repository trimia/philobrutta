/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 23:42:38 by mmariani          #+#    #+#             */
/*   Updated: 2023/02/15 04:13:23 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_input(int argc, char **argv, t_input *input)
{
	input->n_ph = ft_atoi(argv[1]);
	input->tt_die = ft_atoi(argv[2]);
	input->tt_eat = ft_atoi(argv[3]);
	input->tt_sleep = ft_atoi(argv[4]);
	input->havealleat = 1;
	input->some_die = 1;
	if (argc == 6)
		input->n_to_eat = ft_atoi(argv[5]);
	else
		input->n_to_eat = -1;
	input->philo = (t_philo *) malloc (sizeof(t_philo) * input->n_ph);
	if (input->philo == NULL)
		return (-1);
	if (ft_initmutex(input))
		return (-1);
	return (0);
}

static void	init_philo(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->n_ph)
	{
		input->philo[i].id = i + 1;
		input->philo[i].n_eat = 0;
		input->philo[i].end = 0;
		input->philo[i].t_starteating = 0;
		input->philo[i].input = input;
		pthread_mutex_init(&input->philo[i].strv_mutex, NULL);
		input->philo[i].left = &input->forks[i];
		input->philo[i].right = &input->forks[i + 1];
		if (i == input->n_ph - 1)
			input->philo[i].right = &input->forks[0];
		i++;
	}
}

static void	clean(t_input *input)
{
	int		i;
	t_philo	*philo;

	philo = input->philo;
	i = -1;
	while (++i < input->n_ph)
		pthread_mutex_destroy(&input->forks[i]);
	pthread_mutex_destroy(&input->lock);
	pthread_mutex_destroy(&input->die_mutex);
	pthread_mutex_destroy(&input->eat_mutex);
	pthread_mutex_destroy(&input->philo_time);
	free(philo);
	free(input->forks);
}

static void	start(t_input *input)
{
	int	i;

	i = -1;
	input->start_time = ft_get_time();
	while (++i < input->n_ph)
		pthread_create(&input->philo[i].thread, NULL,
			ft_routine, &input->philo[i]);
	ft_monitor(input, -1, 0);
	i = -1;
	while (++i < input->n_ph)
		pthread_join(input->philo[i].thread, NULL);
	clean(input);
}

int	main(int argc, char **argv)
{
	t_input	input;

	if (argc < 5 || argc > 6)
	{
		printf("numero di argomenti erroneo\n");
		return (-1);
	}
	else
	{
		if (ft_check(argc, argv) || init_input(argc, argv, &input))
		{
			printf("errore negli argomenti\n");
			return (-1);
		}
		init_philo(&input);
		start(&input);
	}
}
