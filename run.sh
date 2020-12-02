#!/bin/sh

set -e
meson setup build --buildtype release
cd build
meson compile
cd ..


i=1
while [ "$i" -le 25 ]
do
  test ! -e "build/day$i" || (echo "--> Running day $i" && "build/day$i")
  i=$((i + 1))
done
