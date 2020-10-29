#!/bin/bash
# ./tarzan
# Name: Xinyi Zhu (260924159)


#check if the scipt is passing two arguments
if [ $# != 2 ]
	then
		echo -e "Usage $0 filename tarfile"
		exit 1

# if the tar file is not found
elif [ ! -f $2 ]
	then
		echo -e "Error cannot find tar file $2"
		exit 1

#list out the tar archive and input to grep to find the filename
elif [ ! `tar -xvf $2 -o | grep $1` ]
	then
		echo -e "$1 does not exist in $2"
		exit 1
else 
	#display found message
	echo -e "$1 exits in $2"
fi


