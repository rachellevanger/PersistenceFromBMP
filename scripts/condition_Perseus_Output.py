

import sys
from optparse import OptionParser
from PIL import Image
import os


parser = OptionParser('usage: -d directory ')


parser.add_option("-d", dest="directory",
                  help="The directory with persistence data.")

(options, args) = parser.parse_args()
sDir = options.directory

if not os.path.exists(sDir+"_conditioned"):
    os.makedirs(sDir+"_conditioned")

for fn in os.listdir(sDir):
    if not "betti" in fn and "txt" in fn: # Don't process betti number files
        orig_f = open(sDir+'/'+fn, 'r').read()
        orig_f_lines = orig_f.split('\n')
        new_f = open(sDir+'_conditioned/'+fn, 'w')
        for line in orig_f_lines:
            if line != '':
                p_point = line.split(' ')
                if "DownUp" in sDir: # Process sublevel sets by subtracting one
                    p_point[0] = int(p_point[0]) - 1
                    p_point[1] = max(int(p_point[1]) - 1,-1)
                if "UpDown" in sDir: # Process superlevel sets by subtracting one and taking 255 - x,y
                    p_point[0] = int(p_point[0]) - 1
                    p_point[1] = max(int(p_point[1]) - 1,-1)
                    p_point[0] = 255 - p_point[0]
                    if p_point[1] != -1:
                        p_point[1] = 255 - p_point[1]
                new_f.write("%d %d\n" % (p_point[0], p_point[1]))
            else:
                new_f.write("\n")
        new_f.close()




