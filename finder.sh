#!/bin/bash
# Xinyi Zhu (260924159)


#check if a3config is in the same directory as finder.sh
if [ ! -f $(pwd)/a3config ]
then
	echo "Error cannot find a3config"
	exit 1
fi

source a3config

#check if the variables DIRNAM, EXTENSION and their values exist 
if [ -z `cat a3config | grep "DIRNAME"` ] || [ -z `cat a3config | grep "EXTENSION"` ] || [ -z $DIRNAME ] || [ -z $EXTENSION ]
then
	echo "Error DIRNAME and EXTENSION must be set"
	exit 2
fi

#check if the directory mentioned in DIRNAME exists
if [ ! -d $DIRNAME ]
then
	echo -e "Error directory $DIRNAME does not exist"
	exit 3
fi

#check if the file with expected extension exist in the given directory
if [[ -z `ls $DIRNAME | grep .$EXTENSION` ]]
then
	echo -e "Unable to locate any files with extension $EXTENSION in $DIRNAME"
	exit 0

else
	#store all the matching files in a variable
        filenames=$(ls *.$EXTENSION)

	#check if the value of SHOW is true	
	if [[ $SHOW = "true" ]]
	then
		#iterate over filnames
		for file in $filenames
		do
			#show the full path of the file
			echo -e "$DIRNAME/$file"
			#display the contents of the file
			cat $file
		done
		exit 0

	#when the value of SHOW is not true or empty
	else
		for file in $filenames
		do
			echo -e "$DIRNAME/$file"
		done
		exit 0
	fi
fi






