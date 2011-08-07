//class structure for wavFile

class WavFile{
    private:
	public:
		// properties...
		LONG waRiffId;
		LONG waRiffChunk;
		LONG waWaveId;
		LONG waFmtId;
		LONG waFmtChunk;
		unsigned short int waMonoStereo;
		unsigned short int waChannel;
		LONG waSampleRate;
		LONG waBytesPerSec;
		WORD waBytesPerSample;
		WORD waBitsPer;
		LONG waDataChunk;
		LONG waLengthOfChunk;

		// ASCII stuffable character in bitmap...
		long bmTotalStuffchar;
		unsigned long wavFileSize;

		// methods
		WavFile(char *filename);										// constructor
		int isFileExist(char *filename);								// check file existence
		int readHeader(char *filename);									// read WAVE Header
		int printFileInfo();											// print header variables
		int checkFilesForHiding(char *parentfile, char *childfile);		// check files
		int hide(char *parentfile, char *childfile, char *outputfile); 	// hide into parent
		int unhide(char *parentfile, char *txtfile);					// unhide txt
};
