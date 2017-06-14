# The script compiles the files ending with cpp,
# and if this succeeds, launches the resulting 
# executable, which generates output.mp4.
#
# Finally, the script opens output.mp4 for playback.
#
# To run this script, you need to set (turn on) 
# the execute bit of this file. Use the following
# command for this purpose.
#
#     chmod +x build.sh

c++ *.cpp && ./a.out && open output.mp4

