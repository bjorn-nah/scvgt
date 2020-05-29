# scvgt
 Super Cassette Vision Graphic Tool
 
 Simple command line tool to convert images to Super Cassette Vision binaries.
 
 Usage : scvgt _filename_ _option_
 
 Options can be :
 - -b produce a semi-graphical background binary. It assume the image size is correct (no reseize was make, use 64x60)
 - -s produce a sprite binary. The source image was cropped to the minus multiple of 16x16.
 