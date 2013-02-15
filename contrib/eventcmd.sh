#!/bin/sh

# From Pianobar's github.
# https://github.com/PromyLOPh/pianobar/blob/master/contrib/eventcmd-examples/eventcmd.sh

## Must be placed in ~/.config/pianobar/
# Additionally place the following line in ~/.config/pianobar/config
# event_command = /home/$USER/.config/pianobar/eventcmd.sh

while read L; do
    k="`echo "$L" | cut -d '=' -f 1`"
    v="`echo "$L" | cut -d '=' -f 2`"
    export "$k=$v"
done < <(grep -e '^\(title\|artist\|album\|stationName\|songStationName\|pRet\|pRetStr\|wRet\|wRetStr\|songDuration\|songPlayed\|rating\|coverArt\|stationCount\|station[0-9]*\)=' /dev/stdin) # don't overwrite $1...

case "$1" in
    songstart)
        echo "\"$title\" by \"$artist\" on \"$album\"" > $HOME/.config/pianobar/nowplaying
        ;;  

    *)  
        ;;  
esac
