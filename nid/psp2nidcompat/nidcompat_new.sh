#!/bin/bash

version=3.600.011
dir=/mnt/d/desktop/vitafw/PSP2UPDAT-DevKit-3.600.011

find ${dir} -type f -name *.elf | xargs -I{} ./build/psp2nidcompat new ${version} {} ./db

