#!/bin/sh

echo "compiling ... DDSockets.o"
g++ -o DDSockets.o -c DDSockets.cc -I.

echo "compiling ... DDSMutexLockGuard.o"
g++ -o DDSMutexLockGuard.o -c DDSMutexLockGuard.cc -I.
echo "compiling ... DDSCountDown.o"
g++ -o DDSCountDown.o -c DDSCountDown.cc -I.
echo "compiling ... DDSException.o"
g++ -o DDSException.o -c DDSException.cc -I.
