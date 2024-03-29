/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:45:44 by seonkim           #+#    #+#             */
/*   Updated: 2022/03/21 21:49:02 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_time(t_state *state, t_philo *philo)
{
	pthread_mutex_lock(&state->eating);
	print_philo(state, philo->id, "is eating");
	philo->check_last_meal = now_time();
	philo->eat_count++;
	pthread_mutex_unlock(&state->eating);
	usleep_eating(state);
}

int	eating_philosophers(t_state *state, t_philo *philo)
{
	pthread_mutex_lock(&state->forks[philo->left_fork]);
	print_philo(state, philo->id, "has taken a left fork");
	if (state->philo_cnt == 1)
	{
		pthread_mutex_unlock(&state->forks[philo->left_fork]);
		return (0);
	}
	pthread_mutex_lock(&state->forks[philo->right_fork]);
	print_philo(state, philo->id, "has taken a right fork");
	eating_time(state, philo);
	pthread_mutex_unlock(&state->forks[philo->left_fork]);
	pthread_mutex_unlock(&state->forks[philo->right_fork]);
	if (state->check_all_ate)
		return (0);
	return (1);
}

void	*dining_philosophers(void *philo_void)
{
	t_philo	*philo;
	t_state	*state;

	philo = (t_philo *)philo_void;
	state = philo->state;
	if (philo->id % 2)
		usleep(1000);
	while (!state->die)
	{
		if (!eating_philosophers(state, philo))
			break ;
		print_philo(state, philo->id, "is sleeping");
		usleep_sleeping(state);
		print_philo(state, philo->id, "is thinking");
	}
	return (0);
}

int	end_philosophers(t_state *state, int count)
{
	int	i;
	int	error_check;

	error_check = state->philo_cnt == count;
	if (!error_check)
		state->die = 1;
	i = -1;
	while (++i < count)
		pthread_join(state->philo[i].tid, NULL);
	i = -1;
	while (++i < state->philo_cnt)
		pthread_mutex_destroy(&state->forks[i]);
	free(state->forks);
	free(state->philo);
	pthread_mutex_destroy(&state->eating);
	pthread_mutex_destroy(&state->writing);
	return (error_check);
}

int	philosophers(t_state *state)
{
	int		i;
	void	*philo_void;

	i = -1;
	while (++i < state->philo_cnt)
	{
		philo_void = (void *)&(state->philo[i]);
		state->philo[i].check_last_meal = now_time();
		if (pthread_create(&state->philo[i].tid, NULL, \
			dining_philosophers, philo_void))
			return (end_philosophers(state, i));
	}
	check_death_philosophers(state);
	return (end_philosophers(state, state->philo_cnt));
}
