#!/bin/bash
if [ -e log/latest_log.txt ]; then
  fname=`cat log/latest_log.txt`
else
  fname='movie'
fi
ffmpeg -r 30 -i frames/scene0000%04d.png -codec libx264 -pix_fmt yuv420p -loglevel error log/${fname}.mp4
ls -al log/${fname}.mp4

./delete_frames.sh
