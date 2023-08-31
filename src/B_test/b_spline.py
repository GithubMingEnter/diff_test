import matplotlib.pyplot as plt

import nlopt
from numpy import *
def myfunc(x, grad):
    if grad.size > 0:
        grad[0] = 0.0
        grad[1] = 0.5 / sqrt(x[1])
    return sqrt(x[1])
def myconstraint(x, grad, a, b):
    if grad.size > 0:
        grad[0] = 3 * a * (a*x[0] + b)**2
        grad[1] = -1.0
    return (a*x[0] + b)**3 - x[1]
opt = nlopt.opt(nlopt.LD_MMA, 2)
opt.set_lower_bounds([-float('inf'), 0])
opt.set_min_objective(myfunc)
opt.add_inequality_constraint(lambda x,grad: myconstraint(x,grad,2,0), 1e-8)
opt.add_inequality_constraint(lambda x,grad: myconstraint(x,grad,-1,1), 1e-8)
opt.set_xtol_rel(1e-4)
x = opt.optimize([1.234, 5.678])
minf = opt.last_optimum_value()
print("optimum at ", x[0], x[1])
print("minimum value = ", minf)
print("result code = ", opt.last_optimize_result())

import numpy as np
from scipy.interpolate import BSpline

# Define the control points and knot vector
control_points = np.array([[0, 0], [1, 1], [2, -1], [3, 0]])
knots = [0, 0, 0, 0.5, 1, 1, 1, 1]

# Create the B-spline object
degree = 3
bspline = BSpline(knots, control_points, degree)

# Define the desired endpoint position and tangent
endpoint_position = np.array([4, 1])
endpoint_tangent = np.array([1, 0])

# Calculate the position and tangent of the last control point
last_position = endpoint_position
last_tangent = endpoint_tangent / np.linalg.norm(endpoint_tangent)

# Set the position and tangent of the last control point
control_points[-1] = last_position
bspline.c[-1] = last_tangent

# Evaluate the resulting curve
t_eval = np.linspace(0, 1, 100)
curve_points = bspline(t_eval)

# Plot the curve
import matplotlib.pyplot as plt
plt.plot(curve_points[:, 0], curve_points[:, 1], label='B-spline curve')
plt.plot(control_points[:, 0], control_points[:, 1], 'o-', label='Control points')
plt.legend()
plt.show()



