# Pallindrome program
echo "Welcome to Shell Palindrome Checker !"
echo -n "Enter a number : "
read n

rev=0 # reverse number
num=$n # duplicate number
while [ $num -gt 0 ]
do
    r=$((num%10)) # remainder
    rev=$((rev*10))
    rev=$((rev+r)) # reverse joiner
    num=$((num/10))
done

if [ $rev -eq $n ]
then
    echo "$n is a palindrome."
else
    echo "$n is not a palindrome."
fi

echo -n "Thank you for using Shell Palindrome Checker. Bye Bye !"