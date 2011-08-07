//class structure for bmpFile

class BmpFile {
	public:
		// properties...
		int bmpIdentifier;												//BM identifier
		long bmpFilesize;												//File size
		unsigned short int bmpres1,bmpres2;
		long bmpPixoff;
		long bmpiSize;
		long bmpWidth;													//BMP width
		long bmpHeight;													//BMP height
		unsigned short int bmpPlanes;
		unsigned short int bmpBitsPixel;
		long bmpCompression;											//if BMP is compressed
		long bmpImageSize;
		long bmpXscale;
		long bmpYScale;
		long bmpColor;													//BMP color depth
		long bmpImpCol;
		long bmpTotalStuffablechar;										//ASCII stuffable character in bitmap

		//	methods...
		BmpFile(char *filename);                                		//constructor #
		~BmpFile();                                             		//destructor
		int isFileExist(char *filename);								//checking file existence
		int getDimension(char *filename, long *width, long *height);	//get height & width
		int readHeader(char *filename);									//get the header info #
		int hide(char *bmpfile, char *txtfile, char *output);			//hidding job *
		int unhide(char *bmpfile,char *txtfile);						//unhidding job *
		int checkFilesForHiding(char *bmpfile, char *txtfile);			//gets file ready
		int printFileInfo();
};
