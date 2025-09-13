#!/usr/bin/env bash
g++ $1 -o $1.out
./$1.out
rm -f $1.out
