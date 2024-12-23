echo -n "Enter a string : "
read str # string
echo -n "Enter a character to count occurences : "
read ch # character
c=$(grep -o $ch <<< $str | wc -l)
echo -n "Number of occurences = $c"