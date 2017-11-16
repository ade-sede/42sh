#!/bin/sh

factorial()
{
  if test "$1" -gt "1" ; then
	  i=$(expr $1 - 1)
	  j=$(echo 1)
	  k=$(expr $1 \* $j)
    echo $k
  else
    echo 1
  fi
}


while test 1
do
  echo "Enter a number:"
  read x
  factorial $x
done       
