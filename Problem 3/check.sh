old="output.txt"
new="myout.txt"
#cmp --silent $old $new  && echo '### SUCCESS: Files Are Identical! ###' || echo '### WARNING: Files Are Different! ###'
cmp $old $new
