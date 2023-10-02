/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:21:03 by danimart          #+#    #+#             */
/*   Updated: 2023/10/02 18:14:54 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"
#include "headers/text_colors.h"

t_philo_info	*print_info(t_philo_info *info)
{
	if (!DEBUG || info == NULL)
		return (info);
	printf(INFO_HEADER);
	printf(INFO_NUM, "Philosopher amount", info->amount);
	printf(INFO_NUM, "Time to die", info->die_time);
	printf(INFO_NUM, "Time to eat", info->eat_time);
	printf(INFO_NUM, "Time to sleep", info->sleep_time);
	printf(INFO_NUM, "Times to eat", info->eat_num);
	printf(INFO_FOOTER);
	return (info);
}
