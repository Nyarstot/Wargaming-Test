#ifndef ISEVEN_H
#define ISEVEN_H

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

#endif // !ISEVEN_H