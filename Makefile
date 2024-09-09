build: movies

movies: movies.c
	 gcc movies.c -o movies
	
	
clean:
	rm movies
	
