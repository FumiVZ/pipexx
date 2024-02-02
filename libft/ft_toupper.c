/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:03:59 by vzuccare          #+#    #+#             */
/*   Updated: 2023/11/16 10:51:15 by vzuccare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper( int character )
{
	if (character <= 'z' && character >= 'a')
		return (character = character - 32);
	else if (character == EOF)
		return (-1);
	else
		return (character);
}
