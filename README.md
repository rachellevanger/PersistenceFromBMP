# PersistenceFromBMP

This program works with perseus_4_beta (http://www.sas.upenn.edu/~vnanda/perseus/) to generate persistence diagrams from a collection of bmp images in a common directory.

## To install:

Clone this repository to a working directory.

Download perseus_4_beta (above). Configure the makefile to point to this location. You do not need to compile Perseus for the app to compile.

Configure the rest of the makefile appropriately for your environment. Compile using make.

## To run:

The program (currently) expects a few things:
- All bitmap images have some sort of standard naming scheme with a portion of that name a list of integers in consecutive order.
- All bitmap images are contained in a single directory.
- Another directory has been configured that will house the output persistence diagrams. Here is where the program is extra picky:
  - If you are doing sub-levelset persistence, it expects the following subdirectory within this parent directory: DownUp/Diagrams
  - If you are doing super-levelset persistence, it expects the following subdirectory within this parent directory: UpDown/Diagrams

Items to note for the output files:
- Perseus does not accept zero birth times, so all birth and death values will be shifted by one. Thus, for an input of 0-255 (grayscale values), the birth and death times will appear in the range 1-256.
- Super-levelset persistence is performed by inverting the image and then taking sub-levelset persistence. Don't let this output confuse you!

Arguments to the executable BMPPersistence are as follows:

- filestart // Starting integer for bitmaps
- fileend // Ending integer for bitmaps
- jobDir // Directory with bitmap images
- outDir // Directory containing the persistence diagrams/etc
- jobPattern // Pattern for the bitmap images
- sublevel // Do sublevel sets? (0, 1)
- superlevel // Do superlevel sets? (0, 1)
- isRadial // Do radial persistence? (0, 1)
- center_x // Center of radial filter, for radial only. Else 0.
- center_y // Center of radial filter, for radial only. Else 0.
- radius // Radius of radial filter, for radial only. Else 0.
- filter // Filter pixel values less than this amount. Set to 0 for no filtering.

Example: ./BMPPersistence 1 200 /data/bmp /data/PD %05d.bmp 1 1 1 200 200 150 0

