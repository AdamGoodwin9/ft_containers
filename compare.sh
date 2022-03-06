make fclean
make
make std

./containers > containers.txt
./std > std.txt

diff containers.txt std.txt

# rm containers.txt
# rm std.txt
