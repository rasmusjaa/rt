/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:46:08 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/28 17:30:01 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_itoa_base(int n, char *digits)
{
	char			*str;
	unsigned int	nbr;
	unsigned int	len;
	unsigned int	base;

	base = ft_strlen(digits);
	if (n < 0 && base == 10)
		nbr = (unsigned int)(-n);
	else
		nbr = (unsigned int)n;
	len = (unsigned int)ft_ndigits_base(nbr, base) + (n < 0);
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len--] = '\0';
	while (nbr != 0)
	{
		str[len] = digits[nbr % base];
		nbr /= base;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
