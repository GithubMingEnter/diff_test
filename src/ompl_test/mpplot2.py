# from mpl_toolkits.mplot3d import Axes3D
import numpy
import matplotlib.pyplot as plt
from matplotlib.patches import Circle

data=numpy.loadtxt("path_rrt_star.dat")
T=numpy.arctan2(data[:,0],data[:,1])

plt.scatter(data[:,0],data[:,1],s=80,c=T,alpha=0.5)
plt.show()




# cir1 = Circle(xy = (0.5,0.5),radius=0.25,alpha=0.5)
# data = numpy.loadtxt('path_rrt_star.dat')
# #data1= numpy.loadtxt('obstacle.dat')
# fig = plt.figure()
# ax=fig.add_subplot(111)
# ax.add_patch(cir1)
# #ax = fig.gca(projection='3d')
# plt.plot(data[:,0],data[:,1],'.-')
# plt.hold('on')
# plt.grid('on')
# #plt.fill(data1[:,0],data1[:,1],'.-')
# #plt.hold('on')
# #plt.grid('on')
# plt.show()