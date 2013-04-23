#!/bin/sh

echo "compiling ... DDSocketFunc.o"
g++ -o DDSocketFunc.o -c DDSocketFunc.cc -I.

echo "compiling ... DDSMutexLockGuard.o"
g++ -o DDSMutexLockGuard.o -c DDSMutexLockGuard.cc -I.

echo "compiling ... DDSCountDown.o"
g++ -o DDSCountDown.o -c DDSCountDown.cc -I.

echo "compiling ... DDSException.o"
g++ -o DDSException.o -c DDSException.cc -I.

echo "compiling ... DDSLogger.o"
g++ -o DDSLogger.o -c DDSLogger.cc -I.
