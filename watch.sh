ADDR=$1

while true
do
	file=`inotifywait ./ -r -e CLOSE_WRITE 2> /dev/null | grep -oE '[^ ]+$'`
	echo "Detected $file changed."
	if echo "$file" | grep -v -q -f "ignore_list"
	then
		echo "Copying $file to $REMOTE$file..."
		scp $file $ADDR:~/commsTests
	fi
done
