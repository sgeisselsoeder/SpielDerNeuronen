#!/bin/bash
less world_logfile.log | grep -i stone | cut -d " " -f 7-7 | sed -e "s/,/ /g" > stone.log && less world_logfile.log | grep -i sheep | cut -d " " -f 7-7 | sed -e "s/,/ /g" > sheep.log && less world_logfile.log | grep -i berry | cut -d " " -f 7-7 | sed -e "s/,/ /g" > berry.log && less world_logfile.log | grep -i wolf | cut -d " " -f 7-7 | sed -e "s/,/ /g" > wolf.log
