import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# Read in a numpy array from TempEq.txt
temp = np.loadtxt('TempEq.txt')

# Plot as a heatmap based on extent values between 0.0 and 1.0
# (0.0 is the inital guess and 1.0 is the steady state value, 
# as defined in the C file)
fig = plt.figure(1)
im = plt.imshow(temp,extent=(0.0,1.0,0.0,1.0))
plt.show()
plt.title('Heat Transfer using Jacobian')
# Image saved under Temp.png
fig.savefig('Temp.png')
