#!/usr/bin/python
import matplotlib.pyplot as plt
from matplotlib import cm
from pylab import *
import os    

def plotter(path, filename, out):
	f = "%s/%s" % (path,filename)
	if os.path.getsize(f) == 1:
		return
	x = []
	y = []
	a = [] 
	z = []
	cnt = 1
	read_file = open(f,'r')
	print('File is read.')
	for plot_pair in read_file:
		if plot_pair.isspace():
			continue
		xandy = plot_pair.split()
		a.append(xandy)
		if (int(xandy[1])) == -1:
			xandy[1] = 300
		x.append(int(xandy[0]))
		y.append(int(xandy[1]))
	z.append(cnt)

	for i in range(0,len(a)-1):
		if a[i] == a[i+1]:
			cnt = cnt + 1
			z.append(cnt)
			continue
		else:
			cnt = 1
			z.append(cnt)


	print('Points have been processed. Generating image.')
	
	colors = [float(s) for s in z]
	plt.scatter([float(s) for s in x], [float(t) for t in y], c=colors, s=50.,cmap=cm.hot)

	cbar = plt.colorbar()
	plt.clim(1,5)
	cbar.set_ticks(np.arange(1,6), update_ticks=True)

	plt.plot([0.,300.],[0.,300.], linewidth=2.,color='k')
	plt.axis((0.,300.,0.,300.))
	plt.grid(True, color='k')
	plt.xlabel('Birth')
	plt.ylabel('Death')
	plt.title(r'$\beta_0$')
	print("Saving to: " + str(out) + '/' + str(filename) + ".jpg")
	savefig(str(out) + '/' + str(filename) + ".jpg")
	plt.clf()

	print('Done generating image.')
