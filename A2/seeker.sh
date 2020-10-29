#!/bin/bash
# ./seeker
# Name: Xinyi Zhu (260924159)


cond=0
flag=f
#iterate through all the arguments
for arg in "$@"
do
	#search for pattern argument
	if [[ "$arg" != -c ]] && [[ "$arg" != -a ]] && [[ "$arg" != /* ]] 
	then
		pattern=$arg
		cond=1
	#check if there is path argument
	elif [[ "$arg" = /* ]]
	then 
		path=$arg
		flag=t
		#check if the directory exists
		if [[ ! -d $path ]]
		then
			echo -e "Error $path is not a valid directory"
			exit 1
		fi	
	fi
done

#when none of the argument is pattern
if [ $cond = 0 ]
then
	echo -e "Error missing the pattern argument.\nUsage $0 [-c] [-a] pattern [path]" 
	exit 1 
fi

#when the path argument is not passed
if [ $flag = f ]
then
	#let the current directory be the path
	path=$(pwd)
fi

#if cannot find any file with specific pattern in the path
if [[ -z `ls $path | grep $pattern` ]]
then
	echo -e "Unable to locate any files that has pattern $pattern in its name in $path"
	exit 1
fi


#if both -c and -a are passed
if [ $1 = -c ] && [ $2 = -a ]
then
	#store all the matching files in a variable	
	filename=$(ls $path | grep $pattern)
	#iterate over the filenames
	for file in $filename
	do
		echo -e "==== Contents of $path/$file ===="
		#display the content of the file
		cat $path/$file
	done

#if only -c is passed
elif [ $1 = -c ] && [ $2 != -a ]
then
	#only store one matching file
	filename=$(ls $path | grep $pattern | head -1)
	echo -e "==== Contents of $path/$filename ===="
	cat $path/$filename	

#if only -a is passed
elif [ $1 = -a ]
then	
	#store all the matching files in a variable
	filename=$(ls $path | grep $pattern)
	for file in $filename
	do
		#display the full path for each matching file
		echo -e "$path/$file"
	done
else
	filename=$(ls $path | grep $pattern | head -1)
	echo -e "$path/$filename"	
fi


