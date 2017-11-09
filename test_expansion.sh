echo 1 "IFS=$'\n'; var=$'a\nb'; ls {1,2}\$var"
IFS=$'\n'; var=$'a\nb'; ls {1,2}$var
echo "-------"
echo 2 "IFS=$'\n'; var=$'a\nb'; ls *\$var"
IFS=$'\n'; var=$'a\nb'; ls *$var
echo "-------"
echo 3 "ls \$(\$(ls))"
ls $($(ls)) #sortie d erreur est ecrite
echo "-------"
echo 4 "ls {1,2}\$(dsfdfsdfs)"
ls {1,2}$(dsfdfsdfs)
echo "-------"
echo 5 "ls {\$(fedfs), \$(asdsd)}"
ls {$(fedfs), $(asdsd)}
echo "-------"
echo 6 "ls \$(ls {1,2})aa"
ls $(ls {1,2})aa
