import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

# load data from file
data = np.loadtxt('data.txt')

# extract inputs and outputs as 2-d arrays
x = data[:, 0]
x = np.c_[np.ones_like(x), x]
y = data[:, 1]
y = np.c_[np.ones_like(y), y]
z = data[:, 2]
z = np.c_[np.ones_like(z), z]

fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')
ax.plot_surface(x, y, z, cmap=cm.coolwarm, linewidth=0, antialiased=False)
ax.set_xlabel('in-shuffle')
ax.set_ylabel('out-shuffle')
ax.set_zlabel('loops to restore')
plt.savefig('plot.png')
plt.show()
