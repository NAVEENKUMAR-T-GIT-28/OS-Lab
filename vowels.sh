#!/bin/bash
echo "Enter a character:"
read ch
case $ch in
    [aeiouAEIOU]) echo "$ch is a Vowel" ;;
    *) echo "$ch is not a Vowel" ;;
esac