#!/bin/bash

version=3.600.011
dir=/mnt/d/desktop/vitafw/PSP2UPDAT-DevKit-3.600.011

for filelist in "./db/kernel/*.txt"; do
  for path in ${filelist[@]}; do
    echo ${path}

    find ${dir} -type f -name *.elf | xargs -I{} ./build/psp2nidcompat add ${version} {} ${path} ${path}
  done
done
