≈# usr/bin/bash

mkdir 2_3
cd 2_3
touch $(echo 'for (i=1; i<=9; i++) {print "2_3_0", i, ".py\n"}' | bc)
touch $(echo 'for (i=10; i<=20; i++) {print "2_3_", i, ".py\n"}' | bc)
for FILE in *
do
echo -e 'def main():\n\tpass\nif __name__ == '__main__':\n\tmain()' > "$FILE"
done
