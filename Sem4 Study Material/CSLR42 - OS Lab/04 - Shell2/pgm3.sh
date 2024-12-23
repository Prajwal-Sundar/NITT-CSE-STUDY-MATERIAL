echo -n "Enter username : "
read name
who > test
if grep $name test
then
    echo -n "Logged in"
else
    echo -n "Not Logged in"
fi