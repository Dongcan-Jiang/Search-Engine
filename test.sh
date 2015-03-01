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
$PROGRAM -s index -p "content to say" 0
$PROGRAM -s index -p "When the hath ten one" 1
$PROGRAM -s index -p "Nor armed"
$PROGRAM -s index -b "abridgement" -f
$PROGRAM -s index -b "acquit" -f
$PROGRAM -s index -b "+abridgement +acquit" -f
$PROGRAM -s index -b "abridgement acquit" -f
$PROGRAM -s index -b "about -above" -f
$PROGRAM -s index -b "+(about -above) +abridgement" -f
$PROGRAM -s index -b "(about -above) abridgement" -f
$PROGRAM -s index -b "(about -above) abridgement -(+(about -above) +abridgement)" -f
$PROGRAM -s index -b "(about -above) abridgement -(+(about -above) +abridgement) -acquit" -f
$PROGRAM -s index -p "content to say" 0 -f
$PROGRAM -s index -p "When the hath ten one" 1 -f
$PROGRAM -s index -p "Nor armed" -f