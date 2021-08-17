set +H
read -r

part='(?:\w+(?:-\w+)*)'
user="(?:${part}(?:\.${part})*)"
host="(?:${part}(?:\.${part})+)"
left='(?<![.-])\b'
right='\b(?!-|\.\S)'
addr="${left}${user}@${host}${right}"

grep -oP "$addr" | sort -u | paste -sd \; -
