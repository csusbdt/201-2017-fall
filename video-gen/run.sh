c++ main.cpp || exit
./a.out 3 || exit
mkdir temp
ffmpeg  -y                  \
	-hide_banner        \
        -f rawvideo         \
        -s:v 72x48          \
	-pix_fmt rgb24      \
	-i ./temp/%d.raw  \
	-r 10               \
        -c:v libx264        \
        output.mp4          \
|| exit
rm -f temp/*.raw
rmdir temp 

