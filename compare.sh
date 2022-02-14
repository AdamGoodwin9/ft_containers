make re

./std >> std.txt
./containers >> containers.txt

diff std.txt containers.txt

rm std.txt
rm containers.txt
