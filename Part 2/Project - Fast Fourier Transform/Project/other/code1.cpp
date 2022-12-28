#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
//double byteToDouble( char firstByte, char secondByte );

// WAVE PCM soundfile format (you can find more in https://ccrma.stanford.edu/courses/422/projects/WaveFormat/ )
typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;            // sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size; // subchunk2_size denotes the number of samples.
    //char data; // actual data : Added by tarmizi
} header;

typedef struct header_file* header_p;
int main()

{
    ofstream myFile;
    myFile.open("mizi.txt");


    FILE * infile = fopen("C:\\Users\\win 10\\Documents\\CLION\\pruebas\\inputFFT.wav","rb");     // Open wave file in read mode
    FILE * outfile = fopen("Output.txt","wb");      // Create output ( wave format) file in write mode;
    FILE * svFile;

    int BUFSIZE = 256;                  // BUFSIZE can be changed according to the frame size required (eg:512)
    int count = 0;                      // For counting number of frames in wave file.
    short int buff16[BUFSIZE];              // short int used for 16 bit as input data format is 16 bit PCM audio
    header_p meta = (header_p)malloc(sizeof(header));   // header_p points to a header struct that contains the wave file metadata fields
    int nb;                         // variable storing number of bytes returned

    if (infile)
    {
        fread(meta, 1, sizeof(header), infile);
        //fwrite(meta,1, sizeof(*meta), outfile);


        cout << "first chunk is :" << sizeof(meta->chunk_id) << " bytes in size" << endl;
        cout << "The file is a :" << meta->chunk_id << " format" << endl;
        cout << " Size of Header file is "<<sizeof(*meta)<<" bytes" << endl;
        cout << " Sampling rate of the input wave file is "<< meta->sample_rate <<" Hz" << endl;
        cout << " Number of bits per sample is: "<< meta->bits_per_sample <<"bits" << endl;
        cout << " Size of data in the audio is: " << sizeof(meta->subchunk2_size)<< " bytes" << endl;
        cout << " The number of channels of the file is "<< meta->num_channels << " channels" << endl;
        cout << " The audio format is PCM:"<< meta->audio_format << endl;
        //cout << " The size of actual data is "<< sizeof(meta->data) << "bytes" << endl;

        while (!feof(infile))          //(nb = fread(buff16,1,BUFSIZE,infile))>0
        {
            // Reading data in chunks of BUFSIZE
            //cout << nb <<endl;
            nb = fread(buff16,sizeof(short int),BUFSIZE,infile);
            count++;
            // Incrementing > of frame
            for (int i = 0; i<BUFSIZE; i+=meta->num_channels) //  BUFSIZE = 256, meta->num_channels = 1
            {
                int hi = (signed char) buff16[i + 1]; // always little endian
                int c = (hi << 8) | buff16[i + 0];
                double t = c / 32768.0;
                i += 2;
                myFile << t<< endl;

            }
        }
        cout << " Number of frames in the input wave file are " <<count << endl;

        return 0;
    }
}
//https://stackoverflow.com/questions/20028389/reading-audio-file-in-c