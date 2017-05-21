I downloaded a binary of Doxygen.

~~~
curl -O http://ftp.stack.nl/pub/users/dimitri/Doxygen-1.8.13.dmg
~~~

I generated a configuration file for the project,
which creates a file named _Doxyfile_.

~~~
/Applications/Doxygen.app/Contents/Resources/doxygen -g
~~~

The above command generates a file named _Doxyfile_.
I went read through this file and make adjustments to the
following variables.

~~~
PROJECT_NAME
OUTPUT_DIRECTORY
GENERATE_LATEX
~~~


