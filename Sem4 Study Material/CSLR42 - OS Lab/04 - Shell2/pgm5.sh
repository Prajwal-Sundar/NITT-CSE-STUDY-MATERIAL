# chmod 777 main.sh
echo -n "Enter filename : "
read file
if [[ -x "$file" ]]
then
    echo -n "File '$file' is executable"
else
    echo -n "File '$file' is not executable or found"
fi