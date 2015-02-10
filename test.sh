if [ $WINDIR ]; then
    PROGRAM=./main.exe
else
    PROGRAM=./main
fi

$PROGRAM -s index -b "abridgement"
$PROGRAM -s index -b "acquit"
$PROGRAM -s index -b "+abridgement +acquit"
$PROGRAM -s index -b "abridgement acquit"
$PROGRAM -s index -b "about -above"
$PROGRAM -s index -b "+(about -above) +abridgement"
$PROGRAM -s index -b "(about -above) abridgement"
$PROGRAM -s index -b "(about -above) abridgement -(+(about -above) +abridgement)"
$PROGRAM -s index -b "(about -above) abridgement -(+(about -above) +abridgement) -acquit"
