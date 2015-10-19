#!/bin/sh
while true
do
	file=`inotifywait ./ -r -e CLOSE_WRITE 2> /dev/null | grep -oE '[^ ]+$'`
	echo "$file"
done
