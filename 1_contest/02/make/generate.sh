cat part-1.c >>solution.c
IFS=$'\n'
for line in $(cat ./compile.conf); do
  echo  >>solution.c "  line=\"$line\";";
  echo  >>solution.c "  addline(line);";
done
cat part-2.c >>solution.c