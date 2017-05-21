
a.out : *.cpp *.h
	c++ *.cpp

clean :
	rm -f output.mp4
	rm -f a.out

run : a.out
	./a.out 50
	open output.mp4

docs : *.cpp *.h 
	/Applications/Doxygen.app/Contents/Resources/doxygen


