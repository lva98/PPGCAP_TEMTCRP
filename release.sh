#!/bin/bash
sh build.sh
rm -rf release 
mkdir release
zip -j release-x64-linux.zip build/method_1 build/method_2 build/split
zip -r release-x64-linux.zip bases/*
mv release-x64-linux.zip release
