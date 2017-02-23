
Hoe deze detectors gebruiken op uw eigen computer:

! Je hebt CMake nodig om te builden in Terminal/Command Prompt/..
! Dit veronderstelt ook dat u OpenCV correct is gebouw op uw eigen computer.

1 - Kopieer de map op uw eigen computer.
2 - Open Terminal/Command Prompt/..
3 - Navigeer naar de directory met CMakeLists.txt en main.cpp.
4 - Typ dit commando: cmake ./CMakeLists.txt -DCMAKE_BUILD_TYPE=Release
5 - Het effectief bouwen gebeurt met: cmake —-build . (Het punt is nodig.)
6 - Nu zou je een executable moeten hebben.

Have fun!


OPMERKING:

4 - cmake . -DCMAKE_BUILD_TYPE=Release
5 - make