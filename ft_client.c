/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:31:57 by aoutumur          #+#    #+#             */
/*   Updated: 2025/02/19 16:02:17 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "ft_printf/ft_printf.h"

static void	ft_send_bits(int pid, char c)
{
	int	bit;

	bit = 7;//start with the most significant bit
	while (bit >= 0)//loop from the MSB to the LSB to be able to send the bits in correct order
	{
		if ((c >> bit) & 1) //extract only the last bit, eg. at position 7 (0), 6 (1), 5 (0) etc.
			kill(pid, SIGUSR1);// for 1s
		else
			kill(pid, SIGUSR2); // for 0s
		usleep(42);//delay 2 ensure signal is sent avoiding overwhelming the server
		bit--;
	}

	}
int	main(int argc, char **argv)
{
	int	server_pid; //to save server pid
	int	i;

	i = 0;
	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]); //transform 1st arg to an integer(pid)
		while (argv[2][i]) //loop trhoug 2nd arg & call funciton for each carac
		{
			ft_send_bits(server_pid, argv[2][i]);
			i++;
		}
		ft_send_bits(server_pid, '\0'); //send null carac as termiantion signal
	}
	else
	{
		ft_printf("Error: wrong format.\n");
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
        return (1);
	}
	return (0);
}
