CC = gcc
CFLAGS = -O2 -g -Wall -Werror

all: password_generator

password_generator:
	@echo "[+] Building project..."
	$(CC) $(CFLAGS) -o password_generator ./src/password_generator.c

run: password_generator
	./password_generator

clean:
	@echo "[+] Cleaning..."
	rm -f password_generator
