#!/bin/bash


F_LOOP=`losetup -f`

echo "Setting up loop back device as $F_LOOP"

losetup $F_LOOP disk_mn_fs

mount -t moonfs $F_LOOP mnt

echo "loop back device properly mounted"
