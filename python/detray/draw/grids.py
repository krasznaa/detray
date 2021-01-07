import math
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import patches
import detray.draw.primitives as draw_primitives


# Helper method to draw a rectangle grid
def rect(fig, ax, grid, linecolor='grey', linewidth=0.5, linestyle='dotted'):
    axes = grid['axes']
    data = [
        np.linspace(start=axes[i]['range'][0],
                    stop=axes[i]['range'][1],
                    num=axes[i]['bins'] + 1) for i in range(0, 2)
    ]
    
    for x in data[0]:
        y_min = data[1][0]
        y_max = data[1][-1]
        start = [x, y_min]
        end = [x, y_max]
        draw_primitives.line(fig, ax, start, end, linecolor, linewidth,
                             linestyle)

    for y in data[1]:
        x_min = data[0][0]
        x_max = data[0][-1]
        start = [x_min, y]
        end = [x_max, y]
        draw_primitives.line(fig, ax, start, end, linecolor, linewidth,
                             linestyle)

    ax.margins(0.05)
    plt.show()


# Helper method to draw a polar grid
def polar(fig, ax, grid, linecolor='grey', linewidth=0.5, linestyle='dotted'):
    axes = grid['axes']
    data = [
        np.linspace(start=axes[i]['range'][0],
                    stop=axes[i]['range'][1],
                    num=axes[i]['bins'] + 1) for i in range(0, 2)
    ]
    for phi in data[1]:
        r_min = data[0][0]
        r_max = data[0][-1]
        cos_phi = math.cos(phi)
        sin_phi = math.sin(phi)
        start = [r_min * cos_phi, r_min * sin_phi]
        end = [r_max * cos_phi, r_max * sin_phi]
        draw_primitives.line(fig, ax, start, end, linecolor, linewidth,
                             linestyle)

    for r in data[0]:
        phi_min = data[1][0]
        phi_max = data[1][-1]
        draw_primitives.arc(fig, ax, r, draw_primitives.rad_grad(phi_min),
                            draw_primitives.rad_grad(phi_max), linecolor,
                            linewidth, linestyle)
    ax.margins(0.05)
    plt.show()