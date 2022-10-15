#!bin/bash

directory="/usr/share/man/man3"
while read func
do
  funcgz=$(find $directory -name "$func.*")
  if [[ -z "$funcgz" ]]
  then
    echo ---
  else
    includename=`gunzip -c "$funcgz"`
    includename=${includename#*#include <}
    includename=${includename%%>*}
    echo $includename
  fi
done
