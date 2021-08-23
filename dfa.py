import pandas as pd
import numpy as np
import math
import matplotlib.pyplot as plt

# x = np.array([8, 10, 6, 9, 7, 5, 5, 11, 11, 8, 6, 7, 9, 10, 7, 9])
x = np.array([8, 8,8,8,8,8,8,8,8,4,8,8,8,8,8,8])
plt.plot(x)
plt.show()

# mean (moyenne)
print(x.mean())

# standard deviation
print(x.std())

# variance // pour plusieurs listes ??
variance = 0
for v in x:
  variance = variance + abs(v - x.mean())**2 # abs(v - x.mean())**2 => moyenne
print(variance)
print(variance / x.size)

# standard deviation from variance
stdev = math.sqrt(variance / (x.size))
print(stdev)

# create an array with a cumulative sum of each deviation across the scale

y = np.cumsum(x - np.mean(x))
print(x)
print(y)

# this is basically transforming the normal process into random walk

plt.plot(y)
plt.show()

# create the scales we're going to use
# i.e. how many numbers we're going to have in each scale

scales = (2**np.arange(2, 4.5, 0.5)).astype(np.int)
print("scales : ",scales)

# prepare an array for fluctuations calculation for every scale

fluct = np.zeros(len(scales))
print(fluct)


# making an array with data divided into time windows

# for each scale 

for e, sc in enumerate(scales):
  
  # how many times we have to divide the scale to fit the numbers in each
  # number of windows, number of elements in each window (rows, columns)
  shape = (y.shape[0]//sc, sc)
  print('shape', shape)
  
  # create an array with data divided in windows for each scale (rows, columns)
  X = np.lib.stride_tricks.as_strided(y,shape=shape)
  print('strides',X)

  # create a vector for each row (number columns)
  scale_ax = np.arange(sc)
  print('scale',scale_ax)

#///////////////////////////////////////////////////////////
  print("X.shape[0]", X.shape[0])

  # rows - the number of windows for each scale
  rms = np.zeros(X.shape[0])
  print("rms", rms)
    
  # for each value in the window (each column in a row)
  for w, xcut in enumerate(X):
    # calculate polynomial fit of the cumsum to x in 1D
    # e.g. make a straight line that fits values found in that window row
   
    coeff = np.polyfit(scale_ax, xcut, 1)
    print('xcut', xcut)
    print('scale_ax', scale_ax)
    print('coeff', coeff)

    # use polyfit coefficients to build a straight line
    # this is how we detrend the data
    xfit = np.polyval(coeff, scale_ax)
    print('xfit', xfit)


    # root mean square of the difference between the value and the fit
    rms[w] = np.sqrt(np.mean((xcut-xfit)**2))
    # print('rms',e,rms[e])
    # which is the same as stdev
    # stdv = (xcut-xfit).std()
    print("rms[w]", rms[w])
    print()

  print(rms)
  fluct[e] = np.sqrt(np.mean(rms**2))

# now we have data on all fluctuations
print('fluct',fluct)

alpha = np.polyfit(scales, fluct, 1)
alpha2 = np.polyfit(np.log2(scales), np.log2(fluct), 1)

fluctfit = 2**np.polyval(alpha2,np.log2(scales))


plt.loglog(scales,fluctfit, "r", basex=2,basey=2)
plt.loglog(scales,fluct, "bo",basex=2,basey=2)
plt.show()

fluctfit2 = np.polyval(alpha,scales)

plt.plot(scales,fluctfit2, "r")
plt.plot(scales,fluct, "bo")

plt.show()

print('alpha', alpha)
print('alpha2', alpha2)
# interpretation

# alpha = 0.5 - when the scale increases 2 times the sq root of variance increases about 1.5 times
# alpha = 1 - scale increases 2 times and variance grows 2 times - on the limit between tending to an average and exploding exponentially
# fractal means we find the same kind of logic we find in the small scale on the big scale
# alpha > 1.1 - complex means we increase the period of observation and the logic breaks — there is no stationery mean — things are changing too much (influence from the outside?)
