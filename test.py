import pandas as pd
import numpy as np
import math
import matplotlib.pyplot as plt


scale_ax = [0, 1, 2, 3]
xcut = [0., 2., 0., 1.]

coeff = np.polyfit(scale_ax, xcut, 1)
print(scale_ax)
print(xcut)
print(coeff)
print()


scale_ax = [0, 1, 2, 3]
xcut = [1, 1., 1., 1.]

coeff = np.polyfit(scale_ax, xcut, 1)
print(scale_ax)
print(xcut)
print(coeff)

print()

scale_ax = [0, 1, 2, 3]
xcut = [3, 2., 1., 0.]

coeff = np.polyfit(scale_ax, xcut, 1)
print(scale_ax)
print(xcut)
print(coeff)

xfit = np.polyval(coeff, scale_ax)
print(xfit)
