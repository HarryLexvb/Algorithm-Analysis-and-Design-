steps:

first method: 

$$ g++ -o CharikarPeel.exe CharikarPeel.cpp
$$ ./CharikarPeel.exe <new-airports.txt> toy.log 

second method:
$$ g++ -o CharikarPeel.exe CharikarPeel.cpp
$$ ./runExperim.sh

third method: 

$$ g++ CharikarPeel.cpp -o CharikarPeel -std=gnu++0x -O3
$$ ./CharikarPeel.exe < toy.txt > toy.log


