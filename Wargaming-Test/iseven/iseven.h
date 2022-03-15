#pragma once

// isEven function given by Wargaming
bool wg_isEven(int value)
{
	return value % 2 == 0;
}

// My isEven function
bool isEven(int value)
{
	return (value >> 1) << 1 == value;
}