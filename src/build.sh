#!/bin/sh

echo "compiling ... DDSockets.o"
g++ -o DDSockets.o -c DDSockets.cc -I.

echo "compiling ... DDSMutexLockGuard.o"
g++ -o DDSMutexLockGuard.o -c DDSMutexLockGuard.cc -I.
