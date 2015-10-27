#!/bin/bash

# The destination directory
REMOTE="heungwes@remote.ecf.utoronto.ca:~/Desktop/"
# The directory to watch
WATCH_PATH="./"
# A file containing a list of regexes for files to ignore
IGNORE_LIST="ignore_list"
inotifywait $WATCH_PATH -m -r -e CLOSE_WRITE |
	while read path action file; do
		echo "$file in $path was $action"
		if echo "$file" | grep -v -q -f "$IGNORE_LIST"
		then
			echo "Copying $file to $REMOTE$file..."
			# Actually copy the file
			scp $file $REMOTE$file
		fi
	done
