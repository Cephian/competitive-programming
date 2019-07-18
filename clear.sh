#!/bin/sh

echo '>>> are you sure you want to clear the workspace? (y/n)'
read line

if [ "$line" != 'y' ] && [ $line != 'yes' ]; then
	echo '>>> exiting...'
	exit
fi

find . -maxdepth 1 -type f | grep -vE '.*\.(sh|py)$' | xargs rm

for x in a b c d e f g; do
	cp competitive-programming/template.cpp $x.cpp
done

for x in 1 2 3 4 5; do
	touch $x.in
done


