#usr/bin/bash

mkdir tmp_dir
cd tmp_dir
touch file1 file file3 file4
ls -l > file1
ls -l | grep 3 > file2
echo Hello world > file3
echo mya mya > file4
cat file3 > file1 && cat file4 > file1
cat file1
cat file2
cat file3
cat file4
cd ..
rm -r tmp_dir
