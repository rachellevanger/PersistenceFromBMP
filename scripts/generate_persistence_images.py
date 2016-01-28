#!/usr/bin/python
import os, sys
from plot_persistence_images import plotter
from optparse import OptionParser

parser = OptionParser('usage: -d directory ')


parser.add_option("-d", dest="directory",
                  help="The directory with persistence data.")
parser.add_option("-o", dest="output",
                  help="The directory that it stores the output.")
(options, args) = parser.parse_args()
path = options.directory

outpath = options.output

print(outpath)

dirs = os.listdir(path)
# This would print all the files and directories
for f in dirs:
   plotter(path, f, outpath)
