c++ main.cpp                                                              &&  \
./a.out | ffmpeg -y -hide_banner -f s16le -ar 44100 -ac 1 -i - output.mp3 &&  \
open output.mp3

