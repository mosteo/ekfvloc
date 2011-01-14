#!/usr/bin/env python

import sys

import matplotlib.lines  as draw
import matplotlib.pyplot as figs

file = open(sys.argv[1], 'r')

fig  = figs.figure()
plot = fig.add_subplot(111)

for line in file:
	tokens = line.split()
	try:
		x0 = float(tokens[0])
		y0 = float(tokens[1])
		x1 = float(tokens[2])
		y1 = float(tokens[3])

		seg = draw.Line2D([x0, x1], [y0, y1])
		plot.add_line(seg)
	except ValueError:
		print("Skipped non-segment line")

figs.show()
