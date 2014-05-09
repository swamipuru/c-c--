#!/usr/bin/env python
#_*_ coding: utf-8 _*_
#
# Script `setup` the install/build Simple Calculator.
#
#

#from disutils.core 
import setup, Extension

def run():
  setup(name='pycalc.c',
	version='0.1',
	author='Puru',	
	author_email='paddypuru@gmail.com',
	license='GNU General Public License(GPL)',
#	description="""A simple calculator that works with""",
#		    """whole numbers written in C/Python.""",
	platforms=['Many'],
	ext_modules=[Extension('pycalc',sources=['pycalc.c'])]
 )

#Commands:
#
# ++ clean up temporary files from 'build' command
# ./setup.py clean -a
#
# ++ build everything needed to install
# ./setup.py build
# ++ install everything from build directory
# ./setup.py install -c -02
#

if __name__ == "__main__":
 run()

##End - Code setup.py. ##
