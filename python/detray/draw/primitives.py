import math
import matplotlib.pyplot as plt
from matplotlib import patches
import detray.draw.primitives as draw_primitives

# Simple conversion from rad to grad
def rad_grad(rad) :
    return rad*180./math.pi

# Helper method to draw a line
def line(fig, ax, start, end, linecolor='grey', linewidth=0.5, linestyle='solid', marker=None):
    plt.plot([start[0],end[0]], [start[1],end[1]], color=linecolor, linewidth=linewidth, linestyle=linestyle, figure=fig, marker=marker)

# Helper method to draw a line
def arc(fig, ax, r, phi_min, phi_max, linecolor='grey', linewidth=0.5, linestyle='solid', marker=None):
    arc = patches.Arc((0,0), 2*r, 2*r, angle=0, theta1=phi_min, theta2=phi_max, color=linecolor, linewidth=linewidth, linestyle=linestyle)
    ax.add_patch(arc)