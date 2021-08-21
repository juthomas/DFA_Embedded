#include <stdio.h>
#include <stdlib.h>

float mean(float *tab, size_t tab_size)
{
	float result = 0;

	for (size_t i = 0; i < tab_size; i++)
	{
		result += tab[i];
	}
	return (result / tab_size);
}

float ft_abs(float x)
{
	return (x < 0 ? -x : x);
}

float variance(float *tab, size_t tab_size)
{
	float mean_r = mean(tab, tab_size);
	float result = 0;

	for (size_t i = 0; i < tab_size; i++)
	{
		result += ft_abs(tab[i] - mean_r) * ft_abs(tab[i] - mean_r);
	}
	return (result);
}

float sqrtf(float n){
	// Max and min are used to take into account numbers less than 1
	float lo = 1 < n ? 1 : n;// min(1, n);
	float hi = 1 > n ? 1 : n;// max(1, n);
	float mid;

  // Update the bounds to be off the target by a factor of 10
	while (100 * lo * lo < n)
	{
		lo *= 10;
	}
	while (100 * hi * hi > n)
	{
		hi *= 0.1;
	}
	for (int i = 0 ; i < 100 ; i++)
	{
		mid = (lo+hi)/2;
		if (mid*mid == n)
		{
			return mid;
		}
		if (mid*mid > n) 
		{
			hi = mid;
		}
		else
		{
			lo = mid;
		}
	}
	return mid;
}

float std(float *tab, size_t tab_size)
{
	float variance_r = variance(tab, tab_size);
	return (sqrtf(variance_r / tab_size));
}

float *cumsum(float *tab, size_t tab_size, float offset)
{
	float	*result;
	float	gap = 0;

	result = (float*)malloc(sizeof(float) * tab_size);

	for (size_t i = 0; i < tab_size; i++)
	{
		result[i] = tab[i] + gap + offset;
		gap = tab[i] + gap + offset;
	}
	return (result);
}

void printTab(float *tab, size_t tab_size)
{
	printf("(");
	for (size_t i = 0; i < tab_size; i++)
	{
		printf("%.2f, ", tab[i]);
	}
	printf(")\n");
}

void printIntegerTab(int32_t *tab, size_t tab_size)
{
	printf("(");
	for (size_t i = 0; i < tab_size; i++)
	{
		printf("%d, ", tab[i]);
	}
	printf(")\n");
}


void printDoubleTab(float **tab, size_t y_size, size_t x_size)
{
	for (size_t y = 0; y < y_size; y++)
	{
		printf("[");
		for (size_t x = 0; x < x_size; x++)
		{
			printf("%.2f, ", tab[y][x]);
		}
		printf("]\n");
	}
	printf("\n");
}

float **create_strided_tab(size_t shape_y, size_t shape_x, float *data)
{
	float	**tab = 0;
	size_t	i = 0;
	if ((tab = (float**)malloc(sizeof(float*) * shape_y)) == 0)
	{
		exit(0);
	}
	for (size_t i = 0; i < shape_y; i++)
	{
		tab[i] = (float*)malloc(sizeof(float) * shape_x);
	}
	for (size_t y = 0; y < shape_y; y++)
	{
		for (size_t x = 0; x < shape_x; x++)
		{
			tab[y][x] = data[i++];
		}
	}
	return (tab);
}

int32_t *arrange(int32_t x)
{
	int32_t *array = 0;
	if ((array = (int32_t*)malloc(sizeof(int32_t) * x)) == 0)
	{
		exit(0);
	}
	for (int32_t i = 0; i < x; i++)
	{
		array[i] = i;
	}
	return (array);
}

float	*initialize_float_tab(size_t size, float value)
{
	float	*tab = 0;
	if ((tab = (float*)malloc(sizeof(float) * size)) == 0)
	{
		exit(0);
	}
	for (size_t i = 0; i < size; i++)
	{
		tab[i] = value;
	}
	return (tab);
}

int	main(void)
{
	float x[] = {8, 10, 6, 9, 7, 5, 5, 11, 11, 8, 6, 7, 9, 10, 7, 9};

	printf("Mean(x) : %f\n", mean(x, sizeof(x) / 4));
	printf("Variance(x) : %f\n", variance(x, sizeof(x) / 4));
	printf("std(x) : %f\n", std(x, sizeof(x) / 4));
	float *y = cumsum(x, sizeof(x) / 4, -mean(x, sizeof(x) / 4));
	printf("cumsum : ");
	printTab(y, sizeof(x) / 4);

	float scales[] = {4, 5, 8, 11, 16};
	float fluct[] = {0, 0, 0, 0, 0};

	for (size_t i = 0; i < sizeof(scales) / 4; i++)
	{
		float shape[2];

		shape[0] = (int)(((float)sizeof(x) / (float)4.0) / scales[i]);
		shape[1] = scales[i];
		printf("shape (%f, %f)\n", shape[0], shape[1]);
		float **x_strides = create_strided_tab(shape[0], shape[1], y);
		printf("x_strides : ");
		printDoubleTab(x_strides, shape[0], shape[1]);
		int32_t *scale_ax = arrange(scales[i]);
		printf("scale_ax : ");
		printIntegerTab(scale_ax, scales[i]);
		float *rms = initialize_float_tab(shape[0], 0.0);
		printf("rms : ");
		printTab(rms, shape[0]);
		// printf("?? %f", (float)scale_ax[2]);
		for (size_t y = 0; y < shape[0]; y++)
		{
			printf("xcut : ");
			printTab(x_strides[y], shape[1]);
		}

	}

	return (0);
}