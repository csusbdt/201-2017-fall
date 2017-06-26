Software Development Plan
June 19, 2017

Instructions

1) Create git repository

Create an internet-accessible git repository.
One possible solution is to use GitHub or other similar service.
Another possible solution is to create a git server
on a Raspberry Pi.

Name the repository _genvideo_.

Include the following source code in the genvideo repository.

2) Write program

Write a C++ program that generates a sine wave with frequency 
180 cycles per second in the form of a sequence of audio samples.
Use 16 bits per sample and 44100 samples per second.

3) Write script

Write a script that runs the sine wave program and pipes the 
standard output stream to an instance of ffmpeg.
Use the following command to run ffmpeg.

    ./a.out | ffmpeg -y  -f s16le -ar 44100 -ac 1 -i - output.mp3 

The script should be runnable in the terminal window of one or more 
operating systems.

