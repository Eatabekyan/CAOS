#!/bin/bash

IFS=$'\n'
i=1
declare -A arr
for var1 in $(awk 'BEGIN{FS=","; OFS="\n"} {print $0}' "$1")
do
  j=1
  IFS=$','
  for var2 in $var1
  do
    arr[$i,$j]=$var2
    j=$(($j+1))
  done
  IFS=$'\n'
  i=$(($i+1))  
done

iter=1
usedstolb=1
declare -a used
for (( iter=1; iter < $i; iter++ ))
do
  
  for (( usedstolb=1; usedstolb < $j; usedstolb++ ))
  do
    if [[ ${used[$usedstolb]} != 1 && ${arr[$usedstolb]} != 0 ]]
    then
      used[$usedstolb]=1 
      break
    fi
  done
  if [[ $usedstolb < $j-1 ]]
  then
    used[usedstolb]=1
    for (( i_iter=$iter+1; i_iter < $i; i_iter++ ))
    do
      b=${arr[$i_iter,$usedstolb]}
      for (( j_iter=1; j_iter < $j; j_iter++ ))
      do
        if [[ b != 0 ]]
        then
          X=`echo "scale=20; ${arr[$i_iter,$j_iter]} / $b" | bc`
          X=`echo "scale=20; $X * ${arr[$iter,$usedstolb]}" | bc`
          X=`echo "scale=20; $X - ${arr[$iter,$j_iter]}" | bc`
          arr[$i_iter,$j_iter]=$X
        else
          break
        fi
      done
    done
  fi
done
declare -a answers
j=$(($j-1))
for (( i_iter=$(($i-1)); i_iter > 0; i_iter-- ))
do
  for (( j_iter=1; j_iter < $j; j_iter++ ))
  do
    if [[ ${arr[$i_iter,$j_iter]} != 0 ]]
    then
      answers[j_iter]=`echo "scale=20; ${arr[$i_iter,$j]} / ${arr[$i_iter,$j_iter]}" | bc`
      for (( i1_iter= $(($i_iter-1)); i1_iter > 0; i1_iter-- ))
      do
        z=`echo "scale=20; ${arr[$i1_iter,$j_iter]} * ${answers[$j_iter]}" | bc`
        arr[$i1_iter,$j]=`echo "scale=20; ${arr[$i1_iter,$j]} - $z" | bc`
        arr[$i1_iter,$j_iter]=0
      done
    fi
  done
done

for (( j_iter=1; j_iter < $j; j_iter++ ))
do 
  echo ${answers[$j_iter]}
done
        
        
        
        
      

