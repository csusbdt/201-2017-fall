c++ main.cpp                                                 &&  \
./a.out |                                                        \
ffmpeg -y -hide_banner                                           \
       -f rawvideo -pix_fmt rgb24 -s:v 720x480 -r 60 -i -        \
       -pix_fmt yuv420p -vcodec mpeg4 -an -q:v 5 output.mp4  &&  \
open output.mp4

