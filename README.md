# PersistenceFromBMP

This program works with perseus_4_beta (http://www.sas.upenn.edu/~vnanda/perseus/) to generate persitsence diagrams from a collection of bmp images in a common directory.

Arguments to the executable BMPPersistence are as follows:

  filestart // Starting integer for bitmaps
  fileend // Ending integer for bitmaps
  jobDir // Directory with bitmap images
  outDir // Directory containing the persistence diagrams/etc
  jobPattern // Pattern for the bitmap images
  sublevel // Do sublevel sets? (0, 1)
  superlevel // Do superlevel sets? (0, 1)
  isRadial // Do radial persistence? (0, 1)

  center_x // Center of radial filter, for radial only. Else 0.
  center_y // Center of radial filter, for radial only. Else 0.
  radius // Radius of radial filter, for radial only. Else 0.

  filter // Filter pixel values less than this amount. Set to 0 for no filtering.

Example: ./BMPPersistence 1 200 /data/bmp /data/PD %05d.bmp 1 1 1 200 200 150 0

