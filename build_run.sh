#!/usr/bin/env bash

set -Exeuo pipefail

gcc -o bintree ./bintree.c -fsanitize=address -g3

./bintree

# -d '' - разделение строк нулевым байтом
readarray -d '' files < <(fd -0 ".*\.dot")

for file_in in "${files[@]}"; do
    file_out="${file_in%.dot}.png"
    dot -Tpng -o $file_out $file_in
done
