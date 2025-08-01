/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:19:54 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/01 21:46:30 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philo(t_philo_info *info, unsigned int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->id = id;
	philo->m_state = mutex_init();
	if (philo->m_state == NULL)
		return (NULL);
	philo->state = ALIVE;
	philo->info = info;
	philo->thread_id = 0;
	philo->eat_amount = 0;
	philo->last_meal_ms = 0;
	return (philo);
}
