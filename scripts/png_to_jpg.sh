#!/bin/bash

set -e

if [ $# -ne 1 ]; then
    echo "Usage: $0 <path to dir with png>"
    exit 1
fi
PNG_DIR=$1

for f in "${PNG_DIR}/"*.png; do
    [ -e "$f" ] || continue
    base="${f%.png}"

    echo "Converting $f > $base.jpg"
    ffmpeg -i $f $base.jpg

    if [ $? -eq 0 ]; then
        rm "$f"
    else
        echo "Failed to convert $f"
    fi
done
