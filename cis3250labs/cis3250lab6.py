#!/usr/bin/python

from __future__ import division
from Tkinter import *

import math
import tkMessageBox

xVar = input("input x variable: ")
print xVar , "is your x var"
deltaE = input("input your delta E variable (predefined error value): ")
print deltaE, "is your delta e"


newX = xVar * (math.pi/180)
c = math.sin(newX)
print c , "is your c"

y = 0
k = 1
n = 0

while ((math.fabs(c - y)) > deltaE):
	if (y % 2 == 0):
		y = y + (newX**k)/(math.factorial(k))
		print y
		print "hey"
	else:
		y = y - (newX**k)/(math.factorial(k))
		print y
		print "hoe"
	n = n + 1
	print n, "cycles"
	k = k + 2

print y , "is your final y value"
print "cycled ", n , " total times"