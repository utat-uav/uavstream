ADDR=$1
echo "Sending to: $ADDR"
while true
do
	FILE=`inotifywait ./ -e CLOSE_WRITE 2> /dev/null | grep -oE '[^ ]+$'`
	echo "Attempting to send file: $FILE"
	scp $FILE $ADDR:~/commsTests
done
