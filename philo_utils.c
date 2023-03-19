/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:29:48 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/16 13:12:26 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hold(t_table *table, int time)
{
	long long	i;

	i = get_time();
	while (!table->stop)
	{
		if (get_time() - i >= time)
			break ;
		usleep(45);
	}
}
