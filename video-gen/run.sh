c++ main.cpp || exit
mkdir temp
./a.out 1 || exit
ffmpeg  -y                  \
	-hide_banner        \
        -f rawvideo         \
        -s:v 72x48          \
	-pix_fmt rgb24      \
	-i ./temp/0.raw  \
	-r 10               \
        -c:v libx264        \
        output.mp4          \
|| exit
rm -f temp/*.raw
rmdir temp 

