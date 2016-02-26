# PersistenceFromBMP

This program works with perseus_4_beta (http://www.sas.upenn.edu/~vnanda/perseus/) to generate persistence diagrams from a collection of bmp images in a common directory.

## To install:

Clone this repository to a working directory.

Download perseus_4_beta (above). Configure the makefile to point to this location. You do not need to compile Perseus for the app to compile.

Configure the rest of the makefile appropriately for your environment. Compile using make.

You may also need to install X11 (used by CImg).

## To run:

The program (currently) expects a few things:
- All bitmap images have some sort of standard naming scheme with a portion of that name a list of integers in consecutive order.
- All bitmap images are contained in a subdirectory that sits in a parent directory.
- Another subdirectory has been configured that will house the output persistence diagrams. Here is where the program is extra picky:
  - If you are doing sub-levelset persistence, it expects the following subdirectory within the parent directory: PD/DownUp/Diagrams
  - If you are doing super-levelset persistence, it expects the following subdirectory within the parent directory: PD/UpDown/Diagrams

Items to note for the output files:
- Perseus does not accept zero birth times, so all birth and death values will be shifted by one. Thus, for an input of 0-255 (grayscale values), the birth and death times will appear in the range 1-256.
- Super-levelset persistence is performed by inverting the image and then taking sub-levelset persistence. Don't let this output confuse you!

Arguments to the executable BMPPersistence are as follows:

- filestart // Starting integer for bitmaps
- fileend // Ending integer for bitmaps
- jobDir // Parent directory
- jobPattern // Pattern for the bitmap images
- sublevel // Do sublevel sets? (0, 1)
- superlevel // Do superlevel sets? (0, 1)
- filter // Filter pixel values less than this amount. Set to 0 for no filtering.
- mask // A mask image (bmp) that is 0 for pixels to filter out, nonzero otherwise

Example: ./BMPPersistence 1 200 /data/ bmps/%05d.bmp 1 1 0 /data/img_mask.bmp

