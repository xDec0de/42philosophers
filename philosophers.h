/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:47:13 by danimart          #+#    #+#             */
/*   Updated: 2022/05/31 14:11:48 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>

typedef struct s_philo_info {
	int	amount;
}				t_philo_info;

// philosophers.c
void			print_error(int code);

// input_parser.c
t_philo_info	parse_arguments(int argc, char **args);

#endif