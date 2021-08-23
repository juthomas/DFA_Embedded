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


void printfloatTab(float **tab, size_t y_size, size_t x_size)
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

float *arrange(float x)
{
	float *array = 0;
	if ((array = (float*)malloc(sizeof(float) * x)) == 0)
	{
		exit(0);
	}
	for (int32_t i = 0; i < x; i++)
	{
		array[i] = (float)i;
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
float Ln(float x) {
  int negatif = 0;
  float fois = 1;
  float ajout = 0;
  if(x<=0.0) return 0;
  if(x<1.0) {
    negatif = 1;
    x = 1.0/x;
  }
  while(x >= 10.0) {
    x /= 10.0;
    ajout += 2.302585092994046;
  };
 
  while(x>=1.1) {
    x = sqrtf(x);
    fois *= 2;
  };
  x--;
  float savx = x;
  float i = 2;
  float xp = x*x;
  float quotient = (xp/i);
  float dl = x-quotient;
  while (1.0E-15<quotient) {
    i++;
    xp *= x;
    dl += (xp/i);
    i++;
    xp *= x;
    quotient = (xp/i);
    dl -= quotient;
  }
 
  dl *= fois;
  dl += ajout;
  if(negatif) dl = -dl;
  return dl;
}

float	*polyfit(float *x, float *y, size_t n)
{
	float	*coeff;

	coeff = (float*)malloc(sizeof(float) * 2);
	float meanX = mean(x, n);
	float meanY = mean(y, n);
	float sum1 = 0, sum2 = 0;
	for (int j = 0; j < n; j++)
	{
		sum1 += (x[j] - meanX) * (y[j] - meanY);
		sum2 += (x[j] - meanX) * (x[j] - meanX);
	}
	coeff[0] = sum1 / sum2;
	coeff[1] = meanY - coeff[0] * meanX;
	return (coeff);
}


float	mean_square(float *x, float *y, size_t n)
{
	float sum1 = 0;
	for (int j = 0; j < n; j++)
		sum1 += (x[j] - y[j]) * (x[j] - y[j]);
	return (sqrtf(sum1 / n));
}

float	mean_square2(float *x, size_t n)
{
	float sum1 = 0;
	for (int j = 0; j < n; j++)
		sum1 += x[j] * x[j];
	return (sqrtf(sum1 / n));
}

float	*polyval(float *coeff, float *x, size_t n)
{
	float	*y;

	y = (float*)malloc(sizeof(float) * n);
	for (int j = 0; j < n; j++)
	{
		y[j] = coeff[0] * x[j] + coeff[1];
	}
	return (y);
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
		printfloatTab(x_strides, shape[0], shape[1]);
		float *scale_ax = arrange(scales[i]);
		printf("scale_ax : ");
		printTab(scale_ax, scales[i]);
		float *rms = initialize_float_tab(shape[0], 0.0);
		printf("rms : ");
		printTab(rms, shape[0]);
		// printf("?? %f", (float)scale_ax[2]);
		for (size_t y = 0; y < shape[0]; y++)
		{
			printf("xcut : ");
			printTab(x_strides[y], shape[1]);
			printTab(scale_ax, scales[i]);

			// scale_ax, x_strides[y]    shape[1]
			//    X         Y              size
			
			// printf("A : %f, B : %f\n\n\n", a, b);
			float *coeff = polyfit(scale_ax, x_strides[y], shape[1]);
			printf("Coeff");
			printTab(coeff, 2);
			float *xfit = polyval(coeff, scale_ax, shape[1]);
			printf("xfit");
			printTab(xfit, shape[1]);
			rms[y] = mean_square(x_strides[y], xfit, shape[1]);
			printf("rms[w], %f\n", rms[y]);
			printf("\n");
		}
		fluct[i] = mean_square2(rms, shape[0]);

	}
	printf("fluct ");
	printTab(fluct, sizeof(scales) / 4);
	float *alpha = polyfit(scales, fluct, sizeof(scales) / 4);
	for (int j = 0; j < sizeof(scales) / 4; j++)
	{
		scales[j] = Ln(scales[j]) / Ln(2);
		fluct[j] = Ln(fluct[j]) / Ln(2);
	}
	float *alpha2 = polyfit(scales, fluct, sizeof(scales) / 4);
	printf("alpha ");
	printTab(alpha, 2);
	printf("alpha2 ");
	printTab(alpha2, 2);

	return (0);
}