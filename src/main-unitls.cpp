#include "core.h"

void	ft_putstr_BT(const char *str, BluetoothSerial &BT)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		BT.write(*(str + i));
		i++;
	}
}
