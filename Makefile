fork: forky.c forky_patterns.c
	gcc forky.c forky_patterns.c -o fork

clean:
	rm -f results.txt