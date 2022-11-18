cat <(
	echo I
	echo 1 2
	echo R
	echo 1
	echo I
	echo 2 3
	echo I
	echo 5 6
	echo D 6
	) - | ./client
