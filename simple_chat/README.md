#### Simple chat

Using Qt and Qml sample with unhandled exception

This project for Netbeans IDE 

To correct work unhandled exception in application chat, must copy binary file report from project `report` to root directory `chat` project

## How to compile and run
```
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
cd build/bin

./chat
```

print crash in chat edit to act unhandled exception

## Framework
- google breakpad
- boost stacktrace
- Qt
- qml

## TODO
- CI/CD
- repository bintray
- Test?
