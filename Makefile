fork: forky.c forky_patterns.c
	gcc forky.c forky_patterns.c -o fork

test: fork
	rm -f results.txt
	echo "Pattern 1:" >> results.txt
	./fork 4 1 
	
	echo "\nPattern 2:" >> results.txt
	./fork 4 2 

clean:
	rm -f results.txt