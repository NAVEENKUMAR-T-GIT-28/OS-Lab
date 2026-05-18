#!/bin/bash
echo "Enter two numbers:"
read a b
echo "Before swap: a=$a b=$b"
temp=$a
a=$b
b=$temp
echo "After swap:  a=$a b=$b"