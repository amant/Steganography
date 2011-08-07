Steganography with in still images:

This is the most popular method of Steganography as minor changes in color are unnoticeable to the human eye. We can simply extract the redundant bits in an image and write them back after modification. We can use any kind of data file as a carrier, as long as a handler is provided. The amount of message that can be encrypted depends upon the size of the carrier.

Any color pixel a single dot is representation of a combination of Red-Green-Blue mode (RGB) where each individual RGB component consists of 8 bits.

If letters in ASCII are to be represented within the color pixels, the rightmost digit, called the Least Significant Bit (LSB), can be altered. Any variation in the value of this bit leads to a very minimal variation in color.

example:
A Pixel with RGB value
R: 00 00 00 00
G: 00 00 00 00
B: 00 00 00 00

Ascii I
011 010 001

Now to hide I in a pixel, it will be represented by modifiying LSB.
A single pixedl holding 3 bites of ascii I information.

R: 00 00 00 00
G: 00 00 00 01
B: 00 00 00 01



Help:

To read bmp file

	hidebmp.exe -i blackbuck.bmp

To encode text into bmp file

	hidebmp.exe -e blackbuck.bmp song.txt output.bmp

To decode text from bmp file

	hidebmp.exe -d output.bmp output.txt
	
	
----------------------------------------------------------------------------------	
	
Steganography with in wave files:

Help:

To read wav file

	hidewav.exe -i ding.wav

To encode text into wav file

	hidewav.exe -e ding.wav song.txt output.wav

To decode text from wav file

	hidewav.exe -d output.wav output.txt