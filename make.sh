#/bin/bash


SRC=$(find . -name '*.c')
mkdir -p "build/TP1/" && mkdir -p "build/TP2/"

if [ $# == 1 ]
then
	if [ $1 = "clean" ]
	then
		rm -rfv "build/"
		for file in $(find . -name '*.o')
		do
			rm -fv $file
		done
	else
		echo "Usage:"
		echo "make		Pour compiler tous les fichiers *.c"
		echo "make clean	Pour supprimer les fichiers de compilation"
	fi
else
	for file in $SRC
	do
		name=$(echo $file | cut -d'.' -f2)
		gcc $file -o "build/$name"
	done
fi
