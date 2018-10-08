#!/bin/sh

printf "# "
echo "generated by" $0
echo

nameOfFolder="gamedatasound"

echo "${nameOfFolder}dir = ""$""(""datadir"")""/""@""PACKAGE""@""/sound"

printf "${nameOfFolder}_DATA = "

items=`ls *.wav`

howManyLines=`printf "${items}" | wc -l`
currentLine=0

echo "${items}" | while read line; do
        if [ $currentLine -gt 0 ]; then
                printf "\t\t\t"
        fi

        printf "%s" $line

        if [ $currentLine -lt $howManyLines ]; then
                printf " \\"
        fi
        echo

        currentLine=`expr $currentLine + 1`
done
